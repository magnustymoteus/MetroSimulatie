#include "DesignByContract.h"
#include "components/parser/Parser.h"
int main() {
    Parser parser;
    parser.parseFile("input/input.xml");
    return 0;
}
