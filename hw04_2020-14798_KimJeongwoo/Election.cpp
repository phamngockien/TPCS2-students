#include "Election.hpp"

Election::Election(std::string Electioninfo)
{
    std::stringstream this_election(Electioninfo);
    this_election >> _num_constituencies;
    this_election >> _num_parties;

    _parties.resize(_num_parties);
    for (unsigned int i=0; i<_num_parties; ++i)
    {
        this_election >> _parties[i];
    }

    comp_plur_result();
    comp_prop_result();
}

std::string Election::get_plur_result() const
{
    return ;
}

std::string Election::get_prop_result() const
{
    return ;
}

std::vector<unsigned int> Election::comp_plur_result()
{
    for (unsigned int i=0; i<_num_parties;++i)
    {
        plur_result[i] = i;
    }
    return ;
}

std::vector<unsigned int> Election::comp_prop_result()
{

    return ;
}

/////////////////////////////////////

Constituency::Constituency(std::string ConstituencyInfo, Election election)
{
    std::stringstream this_consti(ConstituencyInfo);
    this_consti >> _constituency;
    this_consti >> _num_voter;
    
    _results.resize(_num_voter);
    for (unsigned int i=0; i<_num_voter; ++i)
    {
        this_consti >> _results[i];
    }

    comp_party_scores(election);
    comp_plur_winner(election, _party_scores);
}

std::string Constituency::get_constituency() const
{
    return _constituency;
}

std::vector<unsigned int> Constituency::comp_party_scores(Election election)
{
    for(auto e: election._parties){
        unsigned int t = 0;
        unsigned int num = 0;
        for (unsigned int i=0; i<_num_voter; ++i)
        {
            if (_results[i] == e) {num += 1;}
        }
        _party_scores[t] = num;
        t += 1;
    }

    return _party_scores;
}

std::string Constituency::comp_plur_winner(Election election, std::vector<unsigned int> party_scores)
{
    unsigned int max_index = 0;
    unsigned int max = party_scores[0];
    for (unsigned i=1; i<party_scores.size(); ++i){
        if (max<party_scores[i]) {max=party_scores[i]; max_index =i;}
    }

    _plur_winner = election._parties[max_index];
    return _plur_winner;
}