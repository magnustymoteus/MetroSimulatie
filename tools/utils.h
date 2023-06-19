//
// Created by dasha on 18.06.2023.
//

#ifndef METROSIMULATIE_UTILS_H
#define METROSIMULATIE_UTILS_H
#include <sstream>


/**
    * @brief Outputs information of the given line
     * @param lijn Line to print
    */
template<typename T>
inline void print(const T& lijn) {
    std::ostringstream oss;
    oss << lijn;
    std::cout << oss.str();
}

#endif //METROSIMULATIE_UTILS_H
