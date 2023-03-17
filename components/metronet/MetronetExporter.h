//
// Created by gruzi on 17/03/2023.
//

#ifndef PROJECT_SOFTWARE_PRACTICUM2_METRONETEXPORTER_H
#define PROJECT_SOFTWARE_PRACTICUM2_METRONETEXPORTER_H

#include "metronet/Metronet.h"

class MetronetExporter {
private:
    MetronetExporter* _initCheck;
public:
    MetronetExporter();
    bool properlyInitialized() const;

    static void outputMetronet(const Metronet &metronet);
};


#endif //PROJECT_SOFTWARE_PRACTICUM2_METRONETEXPORTER_H
