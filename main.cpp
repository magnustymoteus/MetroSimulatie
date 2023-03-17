#include "tools/DesignByContract.h"
#include "metronet/MetronetImporter.h"
#include "components/metronet/MetronetExporter.h"
int main() {
    MetronetImporter parser;
    Metronet metronet = parser.parseFile("input/input.xml");
    MetronetExporter::outputMetronet(metronet);
    //metronet.autoSimulate(5);
    return 0;
}