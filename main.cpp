#include "tools/DesignByContract.h"
#include "components/parser/Parser.h"
int main() {
    Parser parser;
    Metronet metronet = parser.parseFile("input/input.xml");
    metronet.outputFile();
    return 0;
}
