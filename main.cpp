#include "DesignByContract.h"
#include "Metronet/MetronetImporter.h"
#include "components/Metronet/MetronetExporter.h"

int main() {
    MetronetImporter parser;
    Metronet* metronet = parser.parseFile("input/input.xml");
    Metronet* metronet2 = parser.parseFile("input/simple_input.xml");
    metronet2->graphicalSimulation(7);
    metronet->autoSimulate(7);
    MetronetExporter::output(metronet, "output/output.txt");
    MetronetExporter::outputAdvanced(metronet, "output/output_advanced.txt");
    delete metronet;
    return 0;
}