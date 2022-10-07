//
// Created by Jeongil Seo on 6/10/22.
//
// SNU-ID: 2018-17034
//
// Homework 02
//

#ifndef PRIME_H
#define PRIME_H

#include <cmath> // for math functions
#include <list> // for list objects
#include <vector> // for vector objects

//below code is my old algorithm. Check if the number is multiple of prime less than square root of itself.
/*
std::list<int> getPrime_list(int N)
{
    std::list<int> result;
    bool check_prime = true; //check if the mupltiple of other prime
    for(int i=2; i<=N; i++)
    {
        for(int j : result)
        {
            if(j>std::sqrt(i)) break; //until less than sqrt(i), keep checking
            if(i%j==0) check_prime = false;
        }
        if(check_prime) result.push_back(i); //push in list
        check_prime = true;
    }
    return result;
}

std::vector<int> getPrime_vector(int N)
{
    std::vector<int> result;
    bool check_prime = true; //check if the mupltiple of other prime
    for(int i=2; i<=N; i++)
    {
        for(int j : result)
        {
            if(j>std::sqrt(N)) break; //until less than sqrt(i), keep checking
            if(i%j==0) check_prime = false;
        }
        if(check_prime) result.push_back(i); // push in vector
        check_prime = true;
    }
    return result;
}
*/

std::list<int> getPrime_list(int N)
{
    bool *check = new bool[N]; //make base of seive of Erotosthenes
    std::list<int> result;
    for(int i=0; i<N; i++)
    {
        check[i]=true;
    }
    check[0]=false;
    for(unsigned int i=2; i<=std::sqrt(N); i++)
    {
        if(check[i-1]) //check whether the number already deleted or not in seive
        {
            for(unsigned int j=2*i; j<=N; j+=i) check[j-1]=false; //deleting in seive of Erotosthenes
        }
    }
    
    for(int i=0; i<N; i++)
    {
        if(check[i]) result.push_back(i+1); //make bool to int index
    }
    return result;
}

std::vector<int> getPrime_vector(int N)
{
    bool *check = new bool[N]; // make base of seive of Erotosthenes
    std::vector<int> result;
    for(int i=0; i<N; i++)
    {
        check[i]=true;
    }
    check[0]=false;
    for(unsigned int i=2; i<=std::sqrt(N); i++)
    {
        if(check[i-1]) //check whether the number already deleted or not in seive
        {
            for(unsigned int j=2*i; j<=N; j+=i) check[j-1]=false; //deleting in seive of Erotosthenes
        }
    }
    for(int i=0; i<N; i++)
    {
        if(check[i]) result.push_back(i+1); //make bool to int index
    }
    return result;
}

#endif