#ifndef HW03_TEST_HPP
#define HW03_TEST_HPP

#include "hw03.hpp"

// Part 4
/*
I made a test function to test all of the functions at once.
a) Are two test functions enough?
    - Only vector and array was tested here. It might be engough because they are most common containers. However, it could be better to test with 'list', 'float' etc.
b) What other test functions would you write (given more time)
    - Even though the code of main functions will be changed, testing with 2 or 3 dimentional containers would be nice.
c) In what situations could this function break or give bad results?
    - for part 1, when types of the containers are different
    - for part 2, when input container is vector with no element
    - for part 3, when compare the result, computer does not show all of decimal part. It can make mistake
*/

bool run_all_test(){

    bool all_passed = true;

    // initialize input vectors for part 1 & 2
    std::vector<int> a, b;
    a = {1, 3, 2};
    b = {4, 5, 6};
    std::vector<double> c, d;
    c = {1.2, 2.3, 3.4};
    d = {4.3, 5.4, 6.5};
    std::array<int,3> e = {1, 2, 3};
    std::array<int,3> f = {4, 5, 6};

    // Part 1
    // Be careful that we fixed result type as 'std::vector<double>'
    if (sum(a,b) == std::vector<double> {5, 8, 8}){
        std::cout<<"Part 1 test is passed for vector<int>\n";
    } else {
        all_passed = false;
        std::cout<<"Part 1 test is failed for vector<int>\n";
	}

    if (sum(c,d) == std::vector<double> {5.5, 7.7, 9.9}){
        std::cout<<"Part 1 test is passed for vector<double>\n";
    } else {
        all_passed = false;
        std::cout<<"Part 1 test is failed for vector<double>\n";
	}

    if (sum(e,f) == std::vector<double> {5, 7, 9}){
        std::cout<<"Part 1 test is passed for array<int>\n";
    } else {
        all_passed = false;
        std::cout<<"Part 1 test is failed for array<int>\n";
	}
    
    // Part 2
    if (max(c) == 3.4){
        std::cout<<"Part 2 test is passed for vector<double>\n";
    } else {
        all_passed = false;
        std::cout<<"Part 2 test is failed for vector<double>\n";
	}

    if (max(f) == 6){
        std::cout<<"Part 2 test is passed for array<int>\n";
    } else {
        all_passed = false;
        std::cout<<"Part 2 test is failed for array<int>\n";
	}

    // Part 3
    double x = 2;
    std::array<double, 5> y = {1.1, 2.0, 3.0, 4.0, 5.0};
    std::vector<double> z = {1, 2, 3, 4, 5};

    if (evaluate(y,x) == 129.1){
        std::cout<<"Part 3 test is passed for array<double>\n";
    } else {
        all_passed = false;
        std::cout<<"Part 3 test is failed for array<double>\n";
	}

    if (evaluate(z,x) == 129){
        std::cout<<"Part 3 test is passed for array<int>\n";
    } else {
        all_passed = false;
        std::cout<<"Part 3 test is failed for array<int>\n";
	}

    return all_passed;
}

#endif