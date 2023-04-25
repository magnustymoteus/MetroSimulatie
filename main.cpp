#include "DesignByContract.h"
#include "Metronet/MetronetImporter.h"
#include "components/Metronet/MetronetExporter.h"
int main() {
    MetronetImporter parser;
    Metronet metronet = parser.parseFile("input/input.xml");
    MetronetExporter::outputMetronet(metronet, "output/output.txt");
    metronet.autoSimulate(5);
    return 0;
}