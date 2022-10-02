#ifndef KJW_HW01_H
#define KJW_HW01_H


#include <iostream> // for output
#include <vector> // for vector objects

// Part 1
// a function to sum two vectors
std::vector<double> sum(const std::vector<double> &a, const std::vector<double> &b)
{
    std::vector<double> answer;
    // 1) declare answer vector

    for (int i = 0; i < a.size(); ++i){
        answer.push_back(a[i]+b[i]);
    } 
    // 2) extract each element of two vectors which has same position and sum
    // 3) put it in the answer vetor.

    return answer;
}

// Part 2
// a function to compute the dot product of two vectors
double dot(const std::vector<double> &a, const std::vector<double> &b){
    
    double answer = 0;
    // 1) declare answer value

    for (int i = 0; i < a.size(); ++i){
        answer += a[i]*b[i];
    } 
    // 2) extract each element of two vectors which has same position and multiply between them
    // 3) sum all results to compute the dot product

    return answer;
}

// Part 3
// a function to generate a vector of linearly spaced values
const std::vector<double> linspace(const double &start,const double &stop, const int &num_points){

    double interval = (stop - start)/(num_points - 1); 
    // 1) find the interval of space according to the number of points

    std::vector<double> ans;
    // 2) declare answer vector (ans = abbreviation of answer)

    for (int i=0; i < num_points; ++i){
        double x = start + (interval * i);
        ans.push_back(x);
    }
    // 3) starting at 'start', stack the interval one by one and put them in the answer vector

    return ans;
}

// Part 4
// a function to compute the integral (area under y) for two vectors x and y (y = f(x))
double integrate(const std::vector<double> &x, const std::vector<double> &y){
    
    double ans = 0;
    // 1) declare answer value

    for (int i=0; i < x.size()-1; ++i){
        ans += (x[i+1] - x[i]) * ((y[i+1] + y[i])/2);
    }
    // 2) the values of x and y are set, so multiply the base line(x interval) and the height(average of two y values)
    // 3) sum all results to compute the integral

    return ans;
}


#endif