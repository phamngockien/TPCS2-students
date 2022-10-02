//
// Created by Jeongil Seo on 9/29/22.
//
// SNU-ID: 2018-17034
//
// Homework 01
//
// In this homework we will solve several problems related to vectors,
// using the vector object from the standard template library (STL)
// in the std (standard) namespace.

/*
Part 1:
(a) Test function would be written that case of randomly generated input about fixed result.
(b) False positive : When size of vector a is smaller than b
    ex) sum of {1,2},{2,4,6} -> {3,6}
    False negative : When size of vector a is larger than b
    ex) sum of {1,2,3},{2,4} -> error(not exactly {3,5,3})
Part 2:
(a) Test function would be written that more example about randomly generated case.
(b) False positive : When size of vector a is smaller than b
    ex) dot of {1,2},{2,4,6} -> 10
    False negative : When size of vector a is larger than b
    ex dot of {1,2,3},{2,4} -> error(not exactly 10))
Part 3:
(a) Test function would be written that more example about randomly generated case.
(b) False positive :
    False negative : When floating point error occurs (or num_points is 1 or negative)
Part 4:
(a) Test function would be written that more example about randomly generated case.
(b) False positive : When size of vector a is smaller than b
    ex) sum of {1,2},{2,4,6} -> 3
    False negative : When floating point error occurs (or x is not ascending order)
*/
#ifndef TEST_EXAMPLE_H
#define TEST_EXAMPLE_H

#include "test_function.h" //this header file includes all functions in this example
#include <iostream>
#include <vector>

bool run_all_test()
{
//a variable that control if all tests are passed
bool all_passed = true;

std::vector<double> a{1,2,3,5,7};
std::vector<double> b{4,6,7,9,10};
std::vector<double> c{5,8,10,14,17};

//Part 1:
for(int i=0;i<a.size();i++)
{
    if(sum(a,b)[i]!=c[i]) all_passed=false;
}

//Part 2:
if(dot(a,b)!=152) all_passed=false;

//Part 3:
std::vector<double> d{1,3,5,7,9};
for(int i=0;i<d.size();i++)
{
    if(linspace(1,9,5)[i]!=d[i]) all_passed=false;
}

//Part 4:
if(integrate(a,b)!=46.5) all_passed=false;

//print final result
(all_passed) ? std::cout<<"all tests are passed \n" : std::cout<<"there is a failure in our tests! \n";

return all_passed;
}
#endif