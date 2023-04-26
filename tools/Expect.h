//
// Created by gruzi on 26/04/2023.
//

#include <exception>

template<class ExceptionType>
void expect(const bool &expected_condition, const ExceptionType &exception);

#define EXPECT(expected_condition, exception) expect (expected_condition, exception)
