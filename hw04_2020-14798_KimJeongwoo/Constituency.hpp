#ifndef CONSTITUENCY_HPP
#define CONSTITUENCY_HPP

#include<string>
#include<vector>
#include<iostream>
#include<sstream> //for stringstream

class Constituency
{
public:
    Constituency(std::string ConstituencyInfo);
    std::string get_constituency() const;
    std::string get_plur_winner() const;

private:
    std::string party[3] = {"A", "B", "C"};
    std::string _constituency;
    unsigned int _num_voter;
    std::vector<std::string> _results;
    std::vector<unsigned int> _party_scores;
    std::string _plur_winner;
    std::vector<unsigned int> comp_party_scores();
    std::string comp_plur_winner();

    friend class File_Stream;
};

#endif