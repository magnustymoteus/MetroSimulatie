#include "DesignByContract.h"
#include "Metronet/MetronetImporter.h"
#include "components/Metronet/MetronetExporter.h"
int main() {
    // TODO: instead of ->FirstChildElement() / ->NextSiblingElement(),
    //  implement our own function which does a cerr when the element isn't found
    // TODO: hollywood principle for everything
    // TODO: validation for Station and TramType
    // TODO: more consistency checks
    // TODO: more preconditions and postconditions for methods
    // TODO: write contract description for each class and method
    // TODO: (maybe) a separate class for messages
    // TODO: make code more efficient if everything is finished
    MetronetImporter parser;
    Metronet* metronet = parser.parseFile("input/input.xml");
    metronet->autoSimulate(5);
    MetronetExporter::output(metronet, "output/output.txt");
    MetronetExporter::outputAdvanced(metronet, "output/output_advanced.txt");
    delete metronet;
    return 0;
}