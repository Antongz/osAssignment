#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include "Customer.hpp"

std::vector<std::string> fileReader(std::string fileName)
{
    std::vector<std::string> lines;
    std::string = line;
    std::ifstream myfile (fileName);
    //checks that the file was opened properly
    if (myfile.is_open())
    {
        //store each line of the input text file in the vector
        while (myfile.good())
        {
            getline(myfile,line);
            lines.push_back(line);
        }
        myfile.close();
    }
    else
    {
        std::cout << "Unable to open file" << '\n';
    }

    return lines;
}

std::vector<customers> processInput(std::vector<std::string> input)
{

}

int main(int argc, char const *argv[])
{
    // Checks that the correct number of arguments are passed to the program
    if (argc != 2)
    {
        std::cout << "No files or too many files were given" << '\n';
        exit(1);
    }

    std::vector<std::string> input = fileReader(to_string(argv[1]));


    return 0;
}
