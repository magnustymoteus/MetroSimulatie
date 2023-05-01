#include "DesignByContract.h"
#include "Metronet/MetronetImporter.h"
#include "components/Metronet/MetronetExporter.h"
int main() {
    // TODO: only Metrostation type must support multiple tracks (sporen)
    // TODO: more preconditions and postconditions for methods
    // TODO: hollywood principle for everything
    // TODO: (maybe) a separate class for messages
    MetronetImporter parser;
    Metronet* metronet = parser.parseFile("input/multiple_tracks.xml");
    metronet->autoSimulate(7);
    MetronetExporter::output(metronet, "output/output.txt");
    MetronetExporter::outputAdvanced(metronet, "output/output_advanced.txt");
    delete metronet;
    return 0;
}