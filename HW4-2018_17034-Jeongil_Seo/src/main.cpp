//
// Created by Jeongil Seo on 04/11/22.
//
// SNU-ID: 2018-17034
//
// Homework 04
//
// In this homework we will solve several problems related to vectors,
// using the vector object from the standard template library (STL)
// in the std (standard) namespace.

// This program invert the string to encrypted int data by RSA algorithm.
// In this method, N=187, e=3, d=107

//To run this program :
//(g++ main.cpp File_Stream_Prog.cpp Code.cpp)
//./a.exe ../InputFile.txt ../OutputFile.txt

//Answer in Part 2:
//a) if the character is not ascii code, its char vector size is larger then
//original text
//b) There will be needed the case that confirm exact result in every ascii code
//c) if string is too long, memory lack could be occured. And if e is too large, data^e can be over the limit of unsigned interger.

#include"../headers/File_Stream_Prog.hpp"

int main(int argc, const char* argv[])
{
    if (argc != 3) 
    {
        std::cout << "The command to run this program should be:\n";
        std::cout << "./[executable_file_name] [input_file] [output_file]\n";
        std::cout << "For eg., ./a.out Input.txt Output.txt\n";
        return -1; //-1 means we got an error 
    }

    std::string input_path(argv[1]);
    std::string output_path(argv[2]);

    File_Stream stream_eg;
    stream_eg.run(input_path,output_path);

    return 0;
}