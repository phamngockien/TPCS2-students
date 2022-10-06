#ifndef HW02_HPP
#define HW02_HPP

#include <iostream> // for output
#include <vector> // for vector object
#include <list> //for list object
#include <functional> // for iterator in list

// a function to generate a vector of all primes up to a number 'num'
std::vector<int> vec_primes(const int &num){

    std::vector<int> primes;    // declare vector

    for (int i=2; i<num; ++i){
        // pick each number in ascending order

        bool prime = true;

        for (int j=0; j<primes.size(); ++j){
            if ((i % primes[j]) == 0) {
                prime = false;
                // If the number is divided by other primes, it won't be a prime number.
                break;
                // The existence of one divisor(except 1 and itself) is enough to check if it is a prime number. So break to reduce processing time.
            }
        }

        if (prime) {
            primes.push_back(i);
            // only the prime number can be put in the answer vector
        }
    }
    return primes;
}

// a function to generate a list of all primes up to a number 'num'
std::list<int> list_primes(const int &num){

    // the process is similar with vector's
    std::list<int> primes;
    std::list<int>::iterator it;
    // except list should use iterator to do 'for loop'

    for (int i=2; i<num; ++i){

        bool prime = true;

        for (it = primes.begin(); it != primes.end(); ++it){
            if ((i % *it) == 0) {
                prime = false;
                break;
            }
        }

        if (prime) {
            primes.push_back(i);
            // only the prime number can be put in the answer list
        }
    }

    return primes;
}

#endif