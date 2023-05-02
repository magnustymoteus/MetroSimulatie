#include "DesignByContract.h"
#include "Metronet/MetronetImporter.h"
#include "components/Metronet/MetronetExporter.h"
int main() {
    // TODO: more preconditions and postconditions for methods
    // TODO: write tests for everything
    MetronetImporter parser;
    Metronet* metronet = parser.parseFile("input/input.xml");
    metronet->autoSimulate(7);
    MetronetExporter::output(metronet, "output/output.txt");
    MetronetExporter::outputAdvanced(metronet, "output/output_advanced.txt");
    delete metronet;
    return 0;
}