//
// Created by gruzi on 26/04/2023.
//

#include <exception>

template<class ExceptionType>
void throw_if_false(const bool &expected_condition, const ExceptionType &exception);

#define THROW_IF_FALSE(expected_condition, exception) throw_if_false (expected_condition, exception)

template<class ExceptionType>
void cerr_if_false(const bool &expected_condition, const ExceptionType &exception);

#define CERR_IF_FALSE(expected_condition, exception) cerr_if_false (expected_condition, exception)

