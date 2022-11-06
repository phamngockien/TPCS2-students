//We do this because all header files are in the headers folder
//and all source files (.cpp) are in the src folder
#include "../headers/Code.hpp"
#include <cmath>
#include <iostream>

//Constructor
Code::Code(std::string Input_Code)
{
    _Text = Input_Code;
    const unsigned int _N = 187; //11*17
    const unsigned int _e = 3; //3 is relatively prime with 10 and 16
    const unsigned int _d = 107; // 3*107=1(mod 187)
    _Cyrptotext = encryption(_N, _e);
}

//Original Data
std::string Code::get_Text() const
{
    return _Text;
}

//Encrypted Data
std::vector<unsigned int> Code::get_Cyrptotext() const
{
    return _Cyrptotext;
}

//Public Key
unsigned int Code::get_N() const
{
    return _N;
}

unsigned int Code::get_e() const
{
    return _e;
}

std::vector<unsigned int> Code::encryption(const unsigned int &N, const unsigned int &e)
{
    std::vector<char> _Str2Char(_Text.begin(),_Text.end());
    std::vector<unsigned int> _Char2Int(_Text.size());
    for(unsigned int i=0; i<_Text.size(); i++)
    {
        _Char2Int[i]=((int)std::pow((int)_Str2Char[i], e))%N; //Encrypted Data = Data^e (mod N)
    }
    return _Char2Int;
}