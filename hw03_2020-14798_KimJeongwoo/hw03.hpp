#ifndef HW03_HPP
#define HW03_HPP

#include <iostream> // for output
#include <vector> // for vector objects
#include <array> // for array objects
#include <cmath> // for diverse math calculation

// help-function to print container elements
/*
template <typename T>
void print_container(const T &a)
{
    for (int i=0; i<a.size(); ++i){
        std::cout << a[i] << "\t";
    }
    std::cout << std::endl;
}
*/

// Part 1
// a function to add two containers
template <typename T>
std::vector<double> sum(const T &a, const T &b)
// fix result type to deal with vectors and array in one function
// take two containers as parameters
{
  const int num = a.size();
  
  std::vector<double> ans(num);
  // declare answer vector
  // I spent much time to initialize answer vector and array from the same function, but I couldn't find the way.

  for(int i = 0; i < num; ++i) {
    ans[i] = a[i]+b[i];
  } // extract each element and sum, then put into answer vector

  return ans;
}


// Part2
// a function to find the largest value in a container
template <typename T>
decltype(auto) max(const T &a)
// decltype() to determine the container type
{
    auto maximum = a[0];
    // first element to compare

    for (unsigned int i=1; i<a.size(); ++i){
        maximum = (maximum < a[i]) ? a[i]:maximum;
    }
    // compare each element and get maximum
    
    return maximum;
}


// Part 3
// a function that will evaluate the results for a container y with scalar x for input
template <typename Container, typename ring>
auto evaluate(const Container &y, const ring &x) -> ring{
    
    const int sz = y.size();
    // I put 'int sz' inside function for users to use it more easily
    // otherwise, we should call it like 'evaluate<.....>(y,x)' which is inconvenient

    double ans = 0;
    // declare answer value
    // if I set type as auto, then It return int value. Thus, I made it double to show decimal part
    for (unsigned int i=0; i<sz; ++i){
        ans += y[i] * pow(x, i);
    } // calculate and accumulate
    return ans;
}

#endif