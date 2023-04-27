//
// Created by gruzi on 17/03/2023.
//

#ifndef PROJECT_SOFTWARE_PRACTICUM2_METRONETEXPORTER_H
#define PROJECT_SOFTWARE_PRACTICUM2_METRONETEXPORTER_H

#include "Metronet/Metronet.h"

/**
 * This serves as the MetronetExporter, it outputs an instance of Metronet to a text file.
 * @author Patryk Pilichowski
 * @author Daria Matviichuk
 * @date 17/03/2023
 * @version 0.1
 */

class MetronetExporter {
private:
    MetronetExporter* _initCheck;
public:
    MetronetExporter();
    bool properlyInitialized() const;

    static void output(const Metronet* const &metronet, const std::string &pathFile);
    static void outputAdvanced(const Metronet* const &metronet, const std::string &pathFile);
};


#endif //PROJECT_SOFTWARE_PRACTICUM2_METRONETEXPORTER_H
