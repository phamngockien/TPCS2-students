//
// Created by Jeongil Seo on 6/10/22.
//
// SNU-ID: 2018-17034
//
// Homework 02
//

#ifndef TEST_EXP_H
#define TEST_EXP_H

#include <iostream> //for IO
#include <list> // for list objects
#include <vector> // for vector 
#include <ctime> // for measuring time
#include "prime.hpp"

void test_list(int N, bool print = false)
{
    clock_t t_i, t_f;
    double duration;
    t_i = clock();
    std::list<int> result = getPrime_list(N);
    t_f = clock();
    duration = (double)(t_f-t_i); //measuring time

    if(print) //printing list by parameter
    {
        for(int i : result)
        {
            std::cout<<i<<"\t";
        }
    }
    std::cout<<"\n list duration = "<<duration<<" (ms) \n";
    std::cout<<"# of prime = "<<result.size()<<"\n";
}

void test_vector(int N, bool print = false)
{
    clock_t t_i, t_f;
    double duration;
    t_i = clock();
    std::vector<int> result = getPrime_vector(N);
    t_f = clock();
    duration = (double)(t_f-t_i); //measuring time

    if(print) //printing vector by parameter
    {
        for(int i : result)
        {
            std::cout<<i<<"\t";
        }
    }
    std::cout<<"\n vector duration = "<<duration<<" (ms) \n";
    std::cout<<"# of prime = "<<result.size()<<"\n";
}

#endif