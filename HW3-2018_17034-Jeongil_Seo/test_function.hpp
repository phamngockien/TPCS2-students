//
// Created by Jeongil Seo on 27/10/22.
//
// SNU-ID: 2018-17034
//
// Homework 03
//
// In this homework we will solve several problems related to vectors,
// using the vector object from the standard template library (STL)
// in the std (standard) namespace.

#ifndef TEST_FUNC_H
#define TEST_FUNC_H

#include <cmath> //for calculating power
using namespace std;

//part 1:
template <typename T> T add_containers(const T &x, const T &y){
    T result = x; //set intial value of return value
    for(unsigned int i=0; i<x.size(); i++)
    {
        result[i]=x[i]+y[i];
    }
    return result;
}

//part 2:
template <typename T> decltype(auto) get_large(const T &x){
    auto result=x[0]; //set intial value of return value
    for(unsigned int i=0; i<x.size(); i++)
    {
        result = (result>x[i]) ? result : x[i]; //comparing
    }
    return result;
}

//part 3:
template <typename Container, typename ring>
auto evaluate(const Container &y, const ring &x) -> ring
{
    ring result=0.; //set to zero
    for(unsigned int i=0; i<y.size(); i++)
    {
        result +=y[i]*std::pow(x,i); //calculating polynomial
    }
    return result;
}

#endif
