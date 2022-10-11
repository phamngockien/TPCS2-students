#ifndef HW02_TESTING_EXPERIMENTS_HPP
#define HW02_TESTING_EXPERIMENTS_HPP

#include "hw02.hpp"
#include <stdio.h> // to check processing time
#include <time.h> // to check processing time

// a function to compare the processing time between vector and list.
void Compare_vec_list(){
    clock_t vec_start, vec_end, list_start, list_end;
    double vec_result, list_result;

    vec_start = clock(); // start to check time
    std::vector<int> vec = vec_primes(100000);
    vec_end = clock(); // stop to check time
    vec_result = vec_end - vec_start;

    list_start = clock();
    std::list<int> list = list_primes(100000);
    list_end = clock();
    list_result = list_end - list_start;

    std::cout << "The time to compute primes up to 100000 with vector is " << vec_result << "(ms) and with list is " << list_result << "(ms)." << std::endl;

}

// If you want to print the "list" of all primes up to certain number.
// as vector
void print_primes_vec(const int &num)
{
    std::vector<int> vec = vec_primes(num);
    for (auto e : vec) std::cout << e << "\t";

    std::cout << std::endl;
}
// as list
void print_primes_list(const int &num)
{
    std::list<int> list = list_primes(num);
    for (auto e : list) std::cout << e << "\t";

    std::cout << std::endl;
}



#endif