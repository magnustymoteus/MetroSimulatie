//
// Created by gruzi on 15/03/2023.
//

#ifndef PROJECT_SOFTWARE_PRACTICUM2_METRONETVALIDATOR_H
#define PROJECT_SOFTWARE_PRACTICUM2_METRONETVALIDATOR_H

#include "Metronet.h"

/**
 * This serves as the metronet validator, it checks for data consistency in the Metronet class.
 * @author Patryk Pilichowski
 * @author Daria Matviichuk
 * @date 15/03/2023
 * @version 0.1
 */

class MetronetValidator {
private:
    MetronetValidator* _initCheck;

    bool properlyInitialized() const;
public:
    MetronetValidator();
    static void stationsLinkCheck(const Metronet &metronet);
    static void lijnNrExistsCheck(const Metronet &metronet);
    static void tramForSpoorCheck(const Metronet &metronet);
    static void duplicateTramsCheck(const Metronet &metronet);
    static void consistencyCheck(const Metronet &metronet);

};


#endif //PROJECT_SOFTWARE_PRACTICUM2_METRONETVALIDATOR_H
