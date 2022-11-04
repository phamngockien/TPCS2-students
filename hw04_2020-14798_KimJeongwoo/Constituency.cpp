#include "Constituency.hpp"

Constituency::Constituency(std::string ConstituencyInfo)
{
    std::stringstream this_consti(ConstituencyInfo);
    this_consti >> _constituency;
    this_consti >> _num_voter;
    
    _results.resize(_num_voter);
    for (unsigned int i=0; i<_num_voter; ++i)
    {
        this_consti >> _results[i];
    }
    
    comp_party_scores();
    comp_plur_winner();
    
}

std::string Constituency::get_constituency() const
{
    return _constituency;
}

std::string Constituency::get_plur_winner() const
{
    return _plur_winner;
}

std::vector<unsigned int> Constituency::comp_party_scores( )
{
    for(auto e: party){
        unsigned int num = 0;
        for (unsigned int i=0; i<_num_voter; ++i)
        {
            if (_results[i] == e) {num += 1;}
        }
        _party_scores.push_back(num);
    }

    return _party_scores;
}

std::string Constituency::comp_plur_winner()
{
    unsigned int max_index = 0;
    unsigned int max = _party_scores[0];
    for (unsigned i=1; i<_party_scores.size(); ++i){
        if (max<_party_scores[i]) {max=_party_scores[i]; max_index =i;}
    }

    _plur_winner = party[max_index];
    return _plur_winner;
}