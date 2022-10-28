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

#ifndef TEST_EX_H
#define TEST_EX_H

#include <iostream>
#include <vector>
#include <array>
#include "test_function.hpp"
using namespace std;

//print the container
template <typename T> void print_container(T x)
{
    std::cout<<"(";
    for(int i=0; i<x.size(); i++)
    {
        std::cout<<x[i]<<",";
    }
    std::cout<<")";
}

/*
part 4:
a) Each two test case is about vector, array container. It is enough to show how work with container.
b) If more time is given, test about other containers(eg. list, map, stack, que) is needed.
c) In the part 1, if the different type or size of two containers were given, then it will break and give wrong answer.
In the part 2, if calculating the magnitude of data is hard(eg. complex number, string), then it will not work.
In the part 3, the overflow can be occured by the large input value x or y.
*/
//part 4:
void test_1()
{
    std::cout<<"Part 1)\n";

    //testing vector
    std::vector<int> a {1,2,3};
    std::vector<int> b {2,6,2};
    std::vector<int> c=add_containers<std::vector<int>>(a, b);
    std::cout<<"Vector : ";
    print_container(a);
    std::cout<<"+";
    print_container(b);
    std::cout<<"=";
    print_container(c);
    std::cout<<"\n";

    //testing array
    array<int,3> d {3,4,5};
    array<int,3> e {2,6,2};
    array<int,3> f=add_containers<std::array<int,3>>(d, e);
    std::cout<<"Array : ";
    print_container(d);
    std::cout<<"+";
    print_container(e);
    std::cout<<"=";
    print_container(f);
    std::cout<<"\n";
}

void test_2()
{
    std::cout<<"Part 2)\n";

    //testing vector
    std::vector<int> a {1,2,3,4,5};
    std::cout<<"Vector : ";
    print_container(a);
    std::cout<<" -> "<<get_large(a)<<"\n";

    //testing array
    array<int,5> b {1,6,4,10,5};
    std::cout<<"Array : ";
    print_container(b);
    std::cout<<" -> "<<get_large(b)<<"\n";
}

void test_3()
{
    std::cout<<"Part 3)\n";

    //testing vector
    std::vector<int> a {5,4,3,2,1};
    double b=2.0;
    std::cout<<"Vecter : y=";
    print_container(a);
    std::cout<<", x="<<b<<"\n";
    std::cout<<"return="<<evaluate<std::vector<int>,double>(a,b)<<"\n";

    //testing array
    std::array<int,4> c {-1,3,-3,1};
    double d=4.0;
    std::cout<<"Array : y=";
    print_container(c);
    std::cout<<", x="<<d<<"\n";
    std::cout<<"return="<<evaluate<std::array<int,4>,double>(c,d)<<"\n";
}

#endif

