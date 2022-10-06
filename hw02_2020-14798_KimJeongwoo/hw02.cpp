//
// Created by Jeongwoo Kim on 10/6/22.
//
// SNU-ID: 2020-14798
//
// Homework 02
//
// In this homework we will make functions which return list of prime numbers.
// After that we will compare the processing time between vector and list.

#include "hw02_testing_experiments.hpp"

int main(){

    print_primes_vec(100);
    print_primes_list(100);
//    print_primes_vec(100000);
//    print_primes_list(100000);

    Compare_vec_list();
    
    return 0;
}