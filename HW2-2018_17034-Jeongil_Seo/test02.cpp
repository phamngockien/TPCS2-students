//
// Created by Jeongil Seo on 6/10/22.
//
// SNU-ID: 2018-17034
//
// Homework 02
//

/*
g++ test02.cpp
Time taken when N is INT_MAX(O1)
List : 32.268 (s), Vector : 28.406 (s)
# of prime = 105097565

g++ -O3 test02.cpp
Time taken when N is INT_MAX(O1)
List : 22.111 (s), Vector : 19.305 (s)
# of prime = 105097565

g++ -Ofast test02.cpp
Time taken when N is INT_MAX(O1)
List : 22.071 (s), Vector : 18.968 (s)
# of prime = 105097565
*/

#include "testing_experiments.hpp"
#include <limits.h>
#include <iostream>

int main()
{
    test_list(1000, true);
    test_vector(1000, true);
    test_list(INT_MAX);
    test_vector(INT_MAX);
    return 0;
}

