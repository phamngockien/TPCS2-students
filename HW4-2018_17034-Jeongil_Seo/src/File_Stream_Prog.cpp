#include"../headers/File_Stream_Prog.hpp"

void File_Stream::run(const std::string& infilePath,
                      const std::string& outfilePath)
{
    //We need a vector of students' information to store all the data
    std::vector<Code> code_list;

    //Now read the data from the input file
    In_File_Stream infile;
    infile.read_codes_inform(infilePath, code_list);

    //Finally, we write the post-processing data to the output file
    Out_File_Stream outfile;
    outfile.write_codes_result(outfilePath, &code_list);
}


void In_File_Stream::read_codes_inform(const std::string& infilePath,
                                          std::vector<Code> &code_list)
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
            Code s(line);

            //We then store this piece of information to a list for later use
            code_list.push_back(s);
        }
        
        infile.close();
    }

    std::cout << "Finish Reading ..." << std::endl;
}

void Out_File_Stream::write_codes_result(const std::string& outfilePath,
                                            std::vector<Code>* code_list)
{
    std::cout << "Writing to a new file ..." << std::endl;

    //Open file for writing - overwrite the previous data
    std::fstream outfile(outfilePath, std::ios::out);
    if (outfile.is_open())
    {
        for (auto s : *code_list)
        {
            for(unsigned int i=0; i<s.get_Cyrptotext().size(); i++)
            {
                outfile << s.get_Cyrptotext()[i] << " ";
            }
            outfile << "\n";

        }
        
        outfile.close();
    }

}