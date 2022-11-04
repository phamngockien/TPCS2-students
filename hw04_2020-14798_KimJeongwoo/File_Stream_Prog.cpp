#include "File_Stream_Prog.hpp"
#include "test.hpp" // for test the calculation results
#include <cmath> // for calculation

void File_Stream::run(const std::string& infilePath,
                      const std::string& outfilePath)
{
    
    //We need a vector of Constituencies' information to store all the data
    std::vector<Constituency> list;

    //Now read the data from the input file
    In_File_Stream infile;
    infile.read_info(infilePath, list);

    // compute plurality representation result
    unsigned int plur_results[3] = {0,0,0}; // without '={0,0,0}', get error
    std::string a, b, c;
    a ="A"; b ="B"; c ="C";
    for (Constituency e: list){
        if (e._plur_winner == a) {plur_results[0] += 1;} 
        else if (e._plur_winner == b) {plur_results[1]+=1;}
        else if (e._plur_winner == c) {plur_results[2]+=1;}
    }

    // compute proportional representaion result
    unsigned int total_votes[3] = {0,0,0};
    unsigned int total = 0;
    for (Constituency e: list) {
        for (unsigned int i=0; i<3; ++i){
            total_votes[i] += e._party_scores[i];
        }
        total += e._num_voter;
    }
    
    unsigned int prop_results[3] = {0,0,0};
    for (unsigned int i=0; i<3; ++i){
        prop_results[i] += (total_votes[i]*6)/total;
        // '/' operator results 'quotient', so if we apply it first, the calculation become 0
    }

    unsigned int remained_seat = 6 -(prop_results[0]+prop_results[1]+prop_results[2]); // If there is a remained seat, we will give each of it in order of the received votes.    
    while (remained_seat != 0){
        unsigned int x = std::max(total_votes[0], std::max(total_votes[1], total_votes[2]));
        if (x == total_votes[0]) {prop_results[0]+=1; total_votes[0]=0;}
        else if (x == total_votes[1]) {prop_results[1]+=1; total_votes[1]=0;}
        else if (x == total_votes[2]) {prop_results[2]+=1; total_votes[2]=0;}
        remained_seat -= 1;
    }

    run_test(plur_results, prop_results);

    //Finally, we write the post-processing data to the output file
    Out_File_Stream outfile;
    outfile.write_results(outfilePath, &list, plur_results, prop_results);
}


void In_File_Stream::read_info(const std::string& infilePath,
                                          std::vector<Constituency> &list)
{
    std::cout << "Reading from the input file ..." << std::endl;
    
    //Open file for reading
    std::fstream infile(infilePath, std::ios::in);
    if (infile.is_open())
    {
        std::string line;
        while (std::getline(infile,line))
        {
            //Load the information in each line
            //the user-defined constructor will read and parse the information.
            Constituency s(line);

            //We then store this piece of information to a list for later use
            list.push_back(s);
        }
        infile.close();
    }

    std::cout << "Finish Reading ..." << std::endl;
}

void Out_File_Stream::write_results(const std::string& outfilePath, std::vector<Constituency>* list, unsigned int arr1[], unsigned int arr2[])
{
    std::cout << "Writing to a new file ..." << std::endl;

    //Open file for writing - overwrite the previous data
    std::fstream outfile(outfilePath, std::ios::out);
    if (outfile.is_open())
    {
        for (auto s : *list)
        {
            outfile << "In "<< s.get_constituency() << ", ";
            outfile << s.get_plur_winner() << " is won!\n";
        }
        outfile << "\n";
        outfile << "the result of election in plurality representation system is\n";
        outfile << "A: " << arr1[0] << ", B: " << arr1[1] << ", C: " << arr1[2] <<"\n";
        outfile << "If it was proportional representation system, the results would be\n";
        outfile << "A: " << arr2[0] << ", B: " << arr2[1] << ", C: " << arr2[2] <<"\n";

        
        outfile.close();
    }

}