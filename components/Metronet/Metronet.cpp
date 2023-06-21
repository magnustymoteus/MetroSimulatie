//
// Created by gruzi on 12/03/2023.
//

#include "Metronet.h"

#include <iostream>
#include <fstream>
#include <ctime>
#include "utils.h"
#include <cstdlib>
#include <unistd.h>

#include "Exceptions/MetronetInconsistentException.h"

Metronet::Metronet(std::map<std::string, Station*> &newStations, std::multimap<int, Tram*> &newTrams) :
fStations(newStations), fTrams(newTrams), isConsistent(true)
{
    _initCheck = this;
    ENSURE(properlyInitialized(), "Expected Metronet to be properly initialized!");
}
Metronet::Metronet() : isConsistent(true) {
    _initCheck = this;
    ENSURE(properlyInitialized(), "Expected Metronet to be properly initialized!");
}
bool Metronet::properlyInitialized() const {
    return _initCheck == this;
}

void Metronet::setIsConsistent(const bool &newIsConsistent) {
    REQUIRE(this->properlyInitialized(), "Expected Metronet to be properly initialized!");
    isConsistent = newIsConsistent;
    ENSURE(getIsConsistent() == isConsistent, "Expected isConsistent to equal to the setter value!");
}

bool Metronet::getIsConsistent() const {
    REQUIRE(this->properlyInitialized(), "Expected Metronet to be properly initialized!");
    return isConsistent;
}

Metronet::~Metronet() {
    REQUIRE(this->properlyInitialized(), "Expected Metronet to be properly initialized!");
    const std::map<std::string, Station*> & stations = getStations();
    for(std::map<std::string, Station*>::const_iterator iter = stations.begin(); iter!=stations.end();iter++) {
        delete iter->second;
    }
    const std::multimap<int, Tram*> & trams = getTrams();
    for(std::multimap<int, Tram*>::const_iterator iter = trams.begin(); iter != trams.end(); iter++) {
        delete iter->second;
    }
}
void wait(const long &durationInSeconds) {
    clock_t now = clock();
    while(clock()-now < durationInSeconds*CLOCKS_PER_SEC);
}
void Metronet::autoSimulate(const unsigned int &steps, bool printRapportOn) {
    REQUIRE(this->properlyInitialized(), "Expected Metronet to be properly initialized!");
    REQUIRE(steps>0, "Expected steps > 0");
    REQUIRE(isConsistent, "Expected metronet to be consistent in a simulation!");
    std::multimap<int, Tram *> trams = getTrams();
    std::multimap<int, Tram *>::iterator iter = trams.begin();

    //Tram : (stepsUntilDefect, stepsUntilFixed), only stores trams of PCC type
    std::map<Tram*, std::pair<unsigned int, unsigned int> > tramsDefectInfo;
    for (iter = trams.begin(); iter != trams.end(); iter++) {
        if(iter->second->getType() == TramType_PCC)
            tramsDefectInfo.insert(std::make_pair(iter->second, std::make_pair(
                iter->second->getAantalDefecten(),iter->second->getReparatieTijd())));
    }
    for (unsigned int i = 0; i < steps; i++) {
        // Fill alreadyMoved map
        std::map<Tram*, bool> alreadyMoved;
        for(iter = fTrams.begin(); iter != fTrams.end(); iter++){
            alreadyMoved.insert(std::make_pair(iter->second, false));
        }
        wait(1);
        print("Stap "); print(i + 1); print(":\n");
        for (iter = trams.begin(); iter != trams.end(); iter++) {
            print("\t");
            std::string stationName = iter->second->getVolgendeStation()->getNaam();
            int lijnNr = iter->second->getLijnNr();
            if(!isTramOnStation(stationName, lijnNr) || (getTramOnStation(stationName, lijnNr) != 0
                    && !alreadyMoved.at(getTramOnStation(stationName, lijnNr)))) {
                if (tramsDefectInfo.find(iter->second) != tramsDefectInfo.end()) {
                    const unsigned int stepsUntilDefect = tramsDefectInfo.at(iter->second).first;
                    const unsigned int stepsUntilFixed = tramsDefectInfo.at(iter->second).second;
                    if (stepsUntilDefect) tramsDefectInfo.at(iter->second).first--;
                    if (!tramsDefectInfo.at(iter->second).first && stepsUntilFixed)
                        tramsDefectInfo.at(iter->second).second--;
                    if (!stepsUntilDefect && !stepsUntilFixed) {
                        tramsDefectInfo.at(iter->second).first = iter->second->getAantalDefecten();
                        tramsDefectInfo.at(iter->second).second = iter->second->getReparatieTijd();
                    }
                    moveTram(iter->second, stepsUntilDefect > 0);
                } else moveTram(iter->second);
            }else{
                print("Tram "); print(iter->second->getLijnNr()); print(" (");
                print(iter->second->getVoertuigNr()); print(") (");
                print(tramTypeToString(iter->second->getType())); print(") wacht tot volgende station vrij is\n");
            }
            alreadyMoved[iter->second] = true;
        }
    }
    // Print the rapport
    if(printRapportOn) printRapport();
}
bool Metronet::isTramOnStation(const std::string &stationName, const int &spoorNr) const {
    REQUIRE(this->properlyInitialized(), "Expected Metronet to be properly initialized!");
    const std::map<std::string, Station*> & stations = getStations();
    REQUIRE(stations.find(stationName) != stations.end(), "Expected the station to exist in metronet!");
    REQUIRE(stations.at(stationName)->spoorExists(spoorNr), "Expected the station to have the given spoorNr!");
    const std::multimap<int, Tram*> & trams = getTrams();
    for(std::multimap<int, Tram*>::const_iterator iter = trams.begin(); iter != trams.end(); iter++) {
        Station* huidigeStation = iter->second->getHuidigeStation();
        if(iter->second->getLijnNr() == spoorNr && huidigeStation->getNaam() == stationName) return true;
    }
    return false;
}
void Metronet::pushStation(Station* station) {
    REQUIRE(this->properlyInitialized(), "Expected Metronet to be properly initialized!");
    fStations.insert(std::make_pair(station->getNaam(), station));
    ENSURE(fStations.find(station->getNaam()) != fStations.end(), "Expected station to be pushed to fStations!");
}
void Metronet::pushTram(Tram* tram) {
    REQUIRE(this->properlyInitialized(), "Expected Metronet to be properly initialized!");
    fTrams.insert(std::make_pair(tram->getLijnNr(), tram));
    ENSURE(fTrams.find(tram->getLijnNr()) != fTrams.end(), "Expected tram to be pushed to fTrams!");
}
void Metronet::pushSpoor(const std::string& stationName, const int &spoorNr, const std::pair<Station*, Station*> &newSpoor){
    REQUIRE(this->properlyInitialized(), "Expected Metronet to be properly initialized!");
    const std::map<std::string, Station*> &stations = getStations();
    REQUIRE(!stations.empty(), "There are no stations in Metronet!");
    std::map<std::basic_string<char>, Station *> extractedStations = getStations();
    Station* station = extractedStations.at(stationName);
    REQUIRE(station != NULL, "Station with given stationName is not found!");
    station->setSpoor(spoorNr, newSpoor);
}
bool Metronet::tramExists(const int &lijnNr) const {
    REQUIRE(this->properlyInitialized(), "Expected Metronet to be properly initialized!");
    const std::multimap<int, Tram*> & trams = getTrams();
    return trams.find(lijnNr) != trams.end();
}
bool Metronet::spoorExists(const int &lijnNr) const {
    REQUIRE(this->properlyInitialized(), "Expected Metronet to be properly initialized!");
    std::map<std::string, Station*> allStations = getStations();
    for(std::map<std::string, Station*>::iterator stationIterator = allStations.begin();
                                                                            stationIterator != allStations.end(); stationIterator++){
        if(stationIterator->second->spoorExists(lijnNr)){
            return true;
        }
    }
    return false;
}
void Metronet::moveTram(Tram* &tram, const unsigned int &steps) const {
    REQUIRE(this->properlyInitialized(), "Expected Metronet to be properly initialized!");
    const int lijnNr = tram->getLijnNr();
    const int voertuigNr = tram->getVoertuigNr();
    if(steps) {
        tram->setDefect(false);
        Station *huidigeStation = tram->getHuidigeStation();
        unsigned int skippedStations = tram->move(steps);
        print("Tram "); print(lijnNr); print(" ("); print(voertuigNr); print(") ("); print(tramTypeToString(tram->getType()));
                  print(") reed van Station "); print(huidigeStation->getNaam()); print(" (");
                  print(huidigeStation->getType()); print(")"); print(" naar Station ");
                  print(tram->getHuidigeStation()->getNaam()); print(" (");
                  print(tram->getHuidigeStation()->getType()); print(")"); print(".\n");

        if (skippedStations) {
            print("\t\t"); print(skippedStations); print(" halte(s) genegeerd omdat een ");
            print(tramTypeToString(tram->getType())); print(" daar niet mag stoppen.\n");
        }
    } else {
        tram->setDefect(true);
        print("Tram "); print(lijnNr); print(" ("); print(voertuigNr); print(") (");
        print(tramTypeToString(tram->getType())); print(") is defect en wordt gerepareerd.\n");
        tram->increaseTotaleReparatieKost();
        print("\t\tTotale reparatiekosten voor de tram: "); print(tram->getTotaleReparatieKost()); print(" euro.\n");
    }
}
Station* Metronet::retrieveStation(const std::string &naam) const {
    REQUIRE(this->properlyInitialized(), "Expected Metronet to be properly initialized!");
    const std::map<std::string, Station*> & stations = getStations();
    if(stations.find(naam) == stations.end()) return 0;
    return stations.at(naam);
}
Tram* Metronet::retrieveTram(const int &lijnNr, const int &voertuigNr) const{
    REQUIRE(this->properlyInitialized(), "Expected Metronet to be properly initialized!");
    const std::multimap<int, Tram*> & trams = getTrams();
    std::pair <std::multimap<int, Tram*>::const_iterator, std::multimap<int,Tram*>::const_iterator> range =
            trams.equal_range(lijnNr);
    for(std::_Rb_tree_const_iterator<std::pair<const int, Tram *> > i = range.first; i != range.second; i++){
        if(i->second->getVoertuigNr() == voertuigNr){
            return i->second;
        }
    }
    return 0;
}

std::multimap<int, Tram*> Metronet::getTrams() const {
    REQUIRE(this->properlyInitialized(), "Expected Metronet to be properly initialized!");
    return fTrams;
}
void Metronet::setTrams(std::multimap<int, Tram*> &newTrams) {
    REQUIRE(this->properlyInitialized(), "Expected Metronet to be properly initialized!");
    fTrams = newTrams;
    ENSURE(getTrams() == newTrams, "Expected fTrams to equal to setter value!");
}

std::map<std::string, Station *> Metronet::getStations() const {
    REQUIRE(this->properlyInitialized(), "Expected Metronet to be properly initialized!");
    return fStations;
}
void Metronet::setStations(std::map<std::string, Station *> &newStations) {
    REQUIRE(this->properlyInitialized(), "Expected Metronet to be properly initialized!");
    fStations=newStations;
    ENSURE(getStations() == newStations, "Expected fStations to equal to the setter value!");
}
Tram* Metronet::getTramOnStation(const std::string &stationName, const int &spoorNr) const {
    REQUIRE(this->properlyInitialized(), "Expected Metronet to be properly initialized!");
    REQUIRE(fStations.find(stationName) != fStations.end(), "Expected the station to exist in metronet!");
    REQUIRE(fStations.at(stationName)->spoorExists(spoorNr), "Expected the station to have the given spoorNr!");
    for(std::multimap<int, Tram*>::const_iterator iter = fTrams.begin(); iter != fTrams.end(); iter++) {
        Station* huidigeStation = iter->second->getHuidigeStation();
        if(iter->second->getLijnNr() == spoorNr && huidigeStation->getNaam() == stationName) return iter->second;
    }
    return 0;
}

void Metronet::printRapport() const{
    REQUIRE(this->properlyInitialized(), "Expected Metronet to be properly initialized!");
    std::set<std::string> stationTypes = getStationTypes();
    std::set<std::string> tramTypes = getTramTypes();
    print("\n######################## Rapport ########################\n\n");
    print("Aantal stations in het metronet: "); print(fStations.size()); print("\n");
    print("Daarvan:\n");
    std::set<std::string>::iterator iter;
    // Iterate through all station types
    for(iter = stationTypes.begin(); iter != stationTypes.end(); ++iter){
        print("\t- " + *iter + ": "); print(getNumberOfStationsWithGivenType(*iter)); print("\n");
        std::set<Station*> stationsWithType = getStationsWithGivenType(*iter);
        for(std::set<Station*>::const_iterator stationIt = stationsWithType.begin();
                                stationIt != stationsWithType.end(); ++stationIt){
            print("\t\t Station " + (*stationIt)->getNaam() + ". ");
            print("\n");
        }
    }
    print("\nAantal trams in het metronet: "); print(fTrams.size()); print("\n");
    print("Daarvan:\n");
    double totaleKosten = 0;
    // Iterate through all tram types
    for(iter = tramTypes.begin(); iter != tramTypes.end(); ++iter){
        print("\t- " + *iter + ": "); print(getNumberOfTramsWithGivenType(*iter)); print("\n");
        std::set<Tram*> tramsWithType = getTramsWithGivenType(*iter);
        for(std::set<Tram*>::const_iterator tramIt = tramsWithType.begin();
            tramIt != tramsWithType.end(); ++tramIt){
            print("\t\t Totale reparatiekosten voor tram "); print((*tramIt)->getLijnNr()); print(" ("); print((*tramIt)->getVoertuigNr());
            print("): "); print((*tramIt)->getTotaleReparatieKost()); print(" euro.\n");
            totaleKosten += (*tramIt)->getTotaleReparatieKost();
        }
    }
    print("\nTotale reparatiekosten voor alle trams: "); print(totaleKosten); print("\n");
    print("\n#########################################################\n");
}
std::set<std::string> Metronet::getStationTypes() const{
    REQUIRE(this->properlyInitialized(), "Expected Metronet to be properly initialized!");
    std::set<std::string> to_return;
    for(std::map<std::string,Station*>::const_iterator iter = fStations.begin(); iter != fStations.end(); ++iter){
        to_return.insert(iter->second->getType());
    }
    return to_return;
}
std::set<std::string> Metronet::getTramTypes() const{
    REQUIRE(this->properlyInitialized(), "Expected Metronet to be properly initialized!");
    std::set<std::string> to_return;
    for(std::map<int,Tram*>::const_iterator iter = fTrams.begin(); iter != fTrams.end(); ++iter){
        to_return.insert(tramTypeToString(iter->second->getType()));
    }
    return to_return;
}

int Metronet::getNumberOfStationsWithGivenType(const std::string& stationType) const{
    REQUIRE(this->properlyInitialized(), "Expected Metronet to be properly initialized!");
    int numberOfStations = 0;
    for(std::map<std::string, Station*>::const_iterator iter = fStations.begin();
                        iter != fStations.end(); ++iter){
        if(iter->second->getType() == stationType) numberOfStations++;
    }
    return numberOfStations;
}

int Metronet::getNumberOfTramsWithGivenType(const std::string& tramType) const{
    REQUIRE(this->properlyInitialized(), "Expected Metronet to be properly initialized!");
    int numberOfTrams = 0;
    for(std::map<int, Tram*>::const_iterator iter = fTrams.begin();
        iter != fTrams.end(); ++iter){
        if(tramTypeToString(iter->second->getType()) == tramType) numberOfTrams++;
    }
    return numberOfTrams;
}

std::set<Station*> Metronet::getStationsWithGivenType(const std::string& stationType) const{
    REQUIRE(this->properlyInitialized(), "Expected Metronet to be properly initialized!");
    std::set<Station*> stations;
    for(std::map<std::string,Station*>::const_iterator iter = fStations.begin();
                iter != fStations.end(); ++iter){
        if(iter->second->getType() == stationType){
            stations.insert(iter->second);
        }
    }
    return stations;
}

std::set<Tram*> Metronet::getTramsWithGivenType(const std::string& tramType) const{
    REQUIRE(this->properlyInitialized(), "Expected Metronet to be properly initialized!");
    std::set<Tram*> trams;
    for(std::map<int,Tram*>::const_iterator iter = fTrams.begin();
        iter != fTrams.end(); ++iter){
        if(tramTypeToString(iter->second->getType()) == tramType){
            trams.insert(iter->second);
        }
    }
    return trams;
}

std::string Metronet::generateIni() const{
    REQUIRE(this->properlyInitialized(), "Expected Metronet to be properly initialized!");
    const char* pathToImages = "output/GeneratedImages/";
    std::string fileName;
    fileName = intToString(getFileCount(pathToImages));
    std::ofstream outputFile;
    std::string pathFile = pathToImages + fileName + ".ini";
    outputFile.open(pathFile.c_str());
    outputFile << "[General]\n"
                  "size = 1024\n"
                  "backgroundcolor = (0, 0, 0)\n"
                  "type = \"LightedZBuffering\"\n"
                  "eye = (100, 50, 75)\n"
                  "nrFigures = " << getTrams().size() + 1 << "\n";
    outputFile << "nrLights = 1\n"
                  "shadowEnabled = TRUE\n"
                  "shadowMask = 2048\n"
                  "\n"
                  "[Light0]\n"
                  "infinity = FALSE\n"
                  "location = (75, 75, 75)\n"
                  "ambientLight = (1, 1, 1)\n"
                  "diffuseLight = (1, 1, 1)\n"
                  "\n"
                  "[Figure0]\n" // Rails
                  "type = \"ThickLineDrawing\"\n"
                  "m = 4\n"
                  "n = 90\n"
                  "radius = 0.2\n"
                  "scale = 1\n"
                  "rotateX = 0\n"
                  "rotateY = 0\n"
                  "rotateZ = 0\n"
                  "ambientReflection = (0.50, 0.50, 0.50)\n"
                  "diffuseReflection = (0.50, 0.50, 0.50)\n"
                  "center = (0, 0, 0)\n"
                  "color = (1, 1, 1)\n"
                  "nrPoints = ";
    outputFile << getStations().size() << "\n";
    std::set<int> lineNrs = getAllLineNrs();
    int numberOfLines = 0;
    for(std::set<int>::const_iterator it = lineNrs.begin(); it != lineNrs.end(); ++it){
        numberOfLines += getNumberOfStations(*it);
    }
    outputFile << "nrLines = " << numberOfLines << "\n";
    // Points
    for(long unsigned int i = 0; i != getStations().size(); i++){
        double x = 4*std::cos(2*M_PI*i/(getStations().size()));
        double y = 4*std::sin(2*M_PI*i/(getStations().size()));
        if(std::abs(x) < 0.0001) x = 0;
        if(std::abs(y) < 0.0001) y = 0;
        outputFile << "point" << i << " = ("<< x
        << ", " << y << ", 0)\n";
    }
    int i = 0;
    // Lines
    for(std::set<int>::const_iterator it = lineNrs.begin(); it != lineNrs.end(); ++it){
        Station* startStation = 0;
        int lijnNr = *it;
        std::map<std::string,Station*> stations = getStations();
        for(std::map<std::string,Station*>::const_iterator iter = stations.begin(); iter != stations.end(); ++iter){
            if(iter->second->spoorExists(lijnNr)) {
                startStation = iter->second;
                break;
            }
        }
        if (startStation == 0) continue;
        Station* next = startStation->getVolgende(lijnNr);
        do{
            outputFile << "line" << i << " = (" << getIndex(getStations(), next) << ","
                        << getIndex(getStations(), next->getVolgende(lijnNr)) << ")\n";
            next = next->getVolgende(lijnNr);
            i++;
        }while(next != startStation);
        outputFile << "line" << i << " = (" << getIndex(getStations(), next) << ","
                   << getIndex(getStations(), next->getVolgende(lijnNr)) << ")\n";
        i++;
    }
    i = 1;
    // And now trains!
    for(std::map<int, Tram*>::const_iterator it = fTrams.begin(); it != fTrams.end(); ++it){
        outputFile << "[Figure" << i << "]\n";
        outputFile << "type = \"obj\"\n"
                      "src = \"train.obj\"\n"
                      "scale = 0.03\n"
                      "rotateX = 90\n"
                      "rotateY = 0\n"
                      "rotateZ = 90 \n"
                      "center = (";
        int stationNumber = getIndex(getStations(), it->second->getHuidigeStation());
        double x = 4*std::cos(2*M_PI*stationNumber/(getStations().size()));
        double y = 4*std::sin(2*M_PI*stationNumber/(getStations().size()));
        if(std::abs(x) < 0.0001) x = 0;
        if(std::abs(y) < 0.0001) y = 0;
        outputFile << x
                      << ", " << y << ", ";
//        if(it->second->isDefect()) outputFile << "1";
//        else
            outputFile << "0.1";
        outputFile << ")\n";
        i++;
        outputFile << "color = " << it->second->getColor() << "\n"
                      "ambientReflection = " << it->second->getColor() << "\n"
                      "diffuseReflection = (0.00, 0.50, 0.00)\n"
                      "normalOn = false\n";
    }
    // Close file
    outputFile.close();
    return pathFile;
}
std::set<int> Metronet::getAllLineNrs() const{
    REQUIRE(this->properlyInitialized(), "Expected Metronet to be properly initialized!");
    std::set<int> lineNrs;
    for(std::map<int,Tram*>::const_iterator iter = fTrams.begin();
        iter != fTrams.end(); ++iter){
        lineNrs.insert(iter->first);
    }
    return lineNrs;
}

int Metronet::getNumberOfStations(int lijnNr) const{
    REQUIRE(this->properlyInitialized(), "Expected Metronet to be properly initialized!");
    int numberOfStations = 0;
    // Find a station with given lijnNr
    Station* startStation = 0;
    if(!spoorExists(lijnNr)) return numberOfStations;
    for(std::map<std::string,Station*>::const_iterator it = fStations.begin(); it != fStations.end(); ++it){
        if(it->second->spoorExists(lijnNr)) {
            startStation = it->second;
            break;
        }
    }
    if(startStation == 0) return numberOfStations;
    Station* current = startStation->getVolgende(lijnNr);
    numberOfStations++;
    do{
        current = current->getVolgende(lijnNr);
        numberOfStations++;
    } while(current != startStation);
    return numberOfStations;
}
void Metronet::graphicalSimulation(const unsigned int &steps){
    REQUIRE(this->properlyInitialized(), "Expected Metronet to be properly initialized!");
    REQUIRE(steps>0, "Expected steps > 0");
    REQUIRE(isConsistent, "Expected metronet to be consistent in a simulation!");
    unsigned int i = 0;
    while(i != steps + 1){
        std::string iniPath = generateIni();
        char buffer[PATH_MAX];
        if (getcwd(buffer, sizeof(buffer))) {
            std::cout << "Current working directory: " << buffer << std::endl;
        } else {
            std::cerr << "Failed to get current working directory." << std::endl;
        }
        std::string command = std::string("cd ") + buffer +
                               " && " + ENGINE_PATH + std::string(" ") + iniPath;
        print(command + "\n");
        int res = system(command.c_str());
        if(res == 90) return;
        res++;
        // Remove last 3 chars
        command = std::string("eog ") + iniPath.substr(0, iniPath.length() - 3) + "bmp & sleep 1 && xdotool key --window $(xdotool search --name 'Image Viewer') Escape";
        print(command + "\n");
        res = system(command.c_str());
        autoSimulate(1, false);
        i++;
    }
}