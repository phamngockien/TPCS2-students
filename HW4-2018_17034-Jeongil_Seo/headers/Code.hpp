#ifndef CODE_H
#define CODE_H

#include<string>
#include<vector>
#include<iostream>

//Declaration of a class 
//that stores all input parameters loaded from a file
class Code
{
public:

    Code(std::string codeInformation); //User-defined default Constructor

    //member functions to query the data
    std::string get_Text() const; //Raw data
    std::vector<unsigned int> get_Cyrptotext() const; //Encoded data
    unsigned int get_N() const; 
    unsigned int get_e() const;

private:
    std::vector<unsigned int> _Cyrptotext;
    std::string _Text;
    unsigned int _N, _e, _d; //For RSA Encoding
    //RSA key cryptosystem
    std::vector<unsigned int> encryption(const unsigned int &N, const unsigned int &e);
};

#endif

