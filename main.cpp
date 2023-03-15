#include "DesignByContract.h"
#include "components/parser/Parser.h"
int main() {
    Parser parser;
    Metronet metronet = parser.parseFile("input/input.xml");
    return 0;
}
