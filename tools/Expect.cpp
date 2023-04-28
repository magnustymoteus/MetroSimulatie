//
// Created by gruzi on 26/04/2023.
//
#include "Expect.h"

#include <iostream>

#include "MetroObject/Exceptions/VHandleableMetroObjectException.h"
#include "MetroObject/Exceptions/VUnhandleableMetroObjectException.h"
#include "Metronet/Exceptions/MetronetInconsistentException.h"

template<class ExceptionType>
void expect(const bool &expected_condition, const ExceptionType &exception) {
    if(!expected_condition) {
        throw exception;
    }
}
template void expect<VUnhandleableMetroObjectException>
        (const bool &expected_condition, const VUnhandleableMetroObjectException &exception);
template void expect<VHandleableMetroObjectException>
        (const bool &expected_condition, const VHandleableMetroObjectException &exception);
template void expect<MetronetInconsistentException>
        (const bool &expected_condition, const MetronetInconsistentException &exception);

template<class ExceptionType>
void expect_nothrow(const bool &expected_condition, const ExceptionType &exception) {
    if(!expected_condition) {
        std::cerr << exception.what() << std::endl;
    }
}
template void expect_nothrow<VUnhandleableMetroObjectException>
        (const bool &expected_condition, const VUnhandleableMetroObjectException &exception);
template void expect_nothrow<VHandleableMetroObjectException>
        (const bool &expected_condition, const VHandleableMetroObjectException &exception);
template void expect_nothrow<MetronetInconsistentException>
        (const bool &expected_condition, const MetronetInconsistentException &exception);




