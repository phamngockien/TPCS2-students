#ifndef KJW_HW01_TEST_H
#define KJW_HW01_TEST_H

// Part 5
// a) We can test all functions by taking all steps in one process and compare the result.
// b-1) For part1, if we compute float elements, sometimes it goes worng. It's because computer make an error amount when change decimal notation into binary one.
// b-2) For part2, if users input 2 dimensional vector, it will break.
// b-3) For part3, when putting a floating number or decimal fraction into 'num_points'
// b-4) For part4, when the interval of x and y is different


#include "kjw_hw01.h" // load my functions to test
#include <cmath> // for diverse math calculation


bool run_all_test(){

    // a variable that control if all tests are passed
    bool all_passed = true;

    // initialize input vectors for part 1 & 2
    std::vector<double> a = {1, 2, 3};
    std::vector<double> b = {4, 5, 6};
  
    // Part 1
    // test: sum a and b, the answer is {5, 7, 9}
    if (sum(a,b) == std::vector<double> {5, 7, 9}){
        std::cout<<"Part 1 test is passed \n";
    } else {
        all_passed = false;
        std::cout<<"Part 1 test is failed \n";
	}

    // Part 2
    // test: compute the dot product of a and b, the answer is 32
    if (dot(a,b) == 32){
        std::cout<<"Part 2 test is passed \n";
    } else {
        all_passed = false;
        std::cout<<"Part 2 test is failed \n";
	}

    // Part 3
    // test: make linear space vector from 0 to 4 with 5 points, the answer is {0,1,2,3,4}
    if (linspace(0,4,5) == std::vector<double> {0,1,2,3,4}){
        std::cout<<"Part 3 test is passed \n";
    } else {
        all_passed = false;
        std::cout<<"Part 3 test is failed \n";
	}

    // Part 4
    // x is from 0 to 10, 1 linear space
    // y is a function of x, which is 'y = (x-3)^2'
    std::vector<double> x = linspace(0, 10, 11);
    std::vector<double> y;
    for (int i=0; i<x.size(); ++i){
        y.push_back(pow((x[i]-3), 2));
    }
    // test: compute the integral for x and y
    // the answer is 125
    if (integrate(x,y) == 125){
        std::cout<<"Part 4 test is passed \n";
    } else {
        all_passed = false;
        std::cout<<"Part 4 test is failed \n";
	}

    //Finally, print if all test are passed or not
    (all_passed) ? std::cout<<"All tests are passed \n" : std::cout<<"There is a failure in our tests! \n";

    return all_passed;
}

#endif