#ifndef ELECTION_HPP
#define ELECTION_HPP

#include<string>
#include<vector>
#include<iostream>
#include<sstream> //for stringstream

class Election
{
public:
    Election(std::string Electioninfo);
    std::string get_plur_result() const;
    std::string get_prop_result() const;

private:
    unsigned int _num_constituencies;
    unsigned int _num_parties;
    std::vector<std::string> _parties;
    std::vector<unsigned int> comp_plur_result();
    std::vector<unsigned int> comp_prop_result();
    std::vector<int> plur_result;
    std::vector<unsigned int> prop_result;
    friend class Constituency;
};

class Constituency
{
public:
    Constituency(std::string ConstituencyInfo, Election election);
    std::string get_constituency() const;

private:
    std::string _constituency;
    unsigned int _num_voter;
    std::vector<std::string> _results;
    std::vector<unsigned int> comp_party_scores(Election election);
    std::vector<unsigned int> _party_scores;
    std::string comp_plur_winner(Election election, std::vector<unsigned int> _party_scores);
    std::string _plur_winner;
};

#endif