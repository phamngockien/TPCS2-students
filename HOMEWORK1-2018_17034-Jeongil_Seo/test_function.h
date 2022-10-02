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
#ifndef TEST_FUNCTION_H
#define TEST_FUNCTION_H

#include <iostream> // for output
#include <vector> // for vector objects

//Part 1: 
std::vector<double> sum(const std::vector<double> &a, const std::vector<double> &b)
{   
    int i;
    std::vector<double> res(a.size()); //instant for output
    for(i=0; i<a.size(); i++)
    {
        res[i]=a[i]+b[i]; //sum each component
    }
    return res;
}

//Part 2: 
double dot(const std::vector<double> &a, const std::vector<double> &b)
{
    int i;
    double res=0; //instant for output
    for(i=0; i<a.size(); i++)
    {
        res+=a[i]*b[i]; //product each component
    }
    return res;
}

//Part 3: 
const std::vector<double> linspace(const double &start, const double &stop, const int &num_points)
{
    int i;
    std::vector<double> res(num_points); //instant for output
    for(i=0; i<num_points; i++)
    {
        res[i]=start+(stop-start)/(num_points-1)*i; //generate linear spacing
    }
    return res;
}

//Part 4: 
double integrate(const std::vector<double> &x, const std::vector<double> &y)
{
    int i;
    double res=0; //instant for output
    for(i=0; i<x.size()-1; i++)
    {
        res+=(y[i+1]+y[i])/2*(x[i+1]-x[i]); //each area with average height in the interval
    }
    return res;
}
#endif