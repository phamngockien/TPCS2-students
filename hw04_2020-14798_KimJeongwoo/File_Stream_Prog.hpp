#ifndef FILE_STREAM_PROG_H
#define FILE_STREAM_PROG_H

#include<fstream>
#include<string>
#include<vector>
#include<iostream>

#include "Constituency.hpp"

//This class is to run the program
class File_Stream
{
public:
    void run(const std::string& infilePath,
             const std::string& outfilePath);
};

class In_File_Stream
{
public:
    void read_info(const std::string& infilePath,
                              std::vector<Constituency> &Constituency_list);

};

class Out_File_Stream
{
public:
    void write_results(const std::string& outfilePath, std::vector<Constituency>* Constituency_list, unsigned int arr1[], unsigned int arr2[]);
};



#endif