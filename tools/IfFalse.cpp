//
// Created by gruzi on 26/04/2023.
//
#include "IfFalse.h"

#include <iostream>

#include "MetroObject/Exceptions/VHandleableMetroObjectException.h"
#include "MetroObject/Exceptions/VUnhandleableMetroObjectException.h"
#include "Metronet/Exceptions/MetronetInconsistentException.h"

template<class ExceptionType>
void throw_if_false(const bool &expected_condition, const ExceptionType &exception) {
    if(!expected_condition) {
        throw exception;
    }
}
template void throw_if_false<VUnhandleableMetroObjectException>
        (const bool &expected_condition, const VUnhandleableMetroObjectException &exception);
template void throw_if_false<VHandleableMetroObjectException>
        (const bool &expected_condition, const VHandleableMetroObjectException &exception);
template void throw_if_false<MetronetInconsistentException>
        (const bool &expected_condition, const MetronetInconsistentException &exception);

template<class ExceptionType>
void cerr_if_false(const bool &expected_condition, const ExceptionType &exception) {
    if(!expected_condition) {
        std::cerr << exception.what() << std::endl;
    }
}
template void cerr_if_false<VUnhandleableMetroObjectException>
        (const bool &expected_condition, const VUnhandleableMetroObjectException &exception);
template void cerr_if_false<VHandleableMetroObjectException>
        (const bool &expected_condition, const VHandleableMetroObjectException &exception);
template void cerr_if_false<MetronetInconsistentException>
        (const bool &expected_condition, const MetronetInconsistentException &exception);




