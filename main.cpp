#include "DesignByContract.h"
#include "Metronet/MetronetImporter.h"
#include "components/Metronet/MetronetExporter.h"
int main() {
    // TODO: hollywood principle for everything
    // TODO: validator for Station and TramType
    // TODO: more consistency checks
    // TODO: more preconditions and postconditions for methods
    // TODO: write contract description for each class and method
    // TODO: (maybe) a separate class for messages
    MetronetImporter parser;
    Metronet* metronet = parser.parseFile("input/input.xml");
    MetronetExporter::outputMetronet(metronet, "output/output.txt");
    metronet->autoSimulate(5);
    delete metronet;
    return 0;
}