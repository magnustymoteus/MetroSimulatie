#include "tools/DesignByContract.h"
#include "components/parser/Parser.h"
#include "components/metronet/MetronetExporter.h"
int main() {
    Parser parser;
    Metronet metronet = parser.parseFile("input/input.xml");
    MetronetExporter::outputMetronet(metronet);
    metronet.autoSimulate(5);
    return 0;
}
