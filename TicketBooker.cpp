//Rory Martin a1740203
//William Godfrey a1743033

#include <algorithm>
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include <cstddef>

#include "Customer.hpp"
#include "Queue.hpp"
#include "OperatingSystem.hpp"

using namespace std;

//gets the input from the input.txt file
vector<string> fileReader(string fileName)
{
    vector<string> lines;
    string line;
    ifstream myfile (fileName);
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
        cout << "Unable to open file" << '\n';
    }

    return lines;
}

//Sort the input into a vector of customers
vector<Customer*> processInput(vector<string> input)
{

    string name;
    int arrivalTime;
    int priority;
    int currentAge;
    int numTickets;
    vector<Customer*> customers;
    Customer* temp;
    //iterates through input vector, producing a new customer each time
    //note: is input.size()-1 as last line doubled.
    for (int i = 0; i < input.size()-1; i++)
    {
        stringstream ss;
        //sorting input values
        ss << input.at(i);
        ss >> name;
        ss >> arrivalTime;
        ss >> priority;
        ss >> currentAge;
        ss >> numTickets;
        temp = new Customer(name, arrivalTime, priority,currentAge, numTickets);
        customers.push_back(temp);
    }

    return customers;
}


int main(int argc, char const *argv[]) {
    // Checks that the correct number of arguments are passed to the program
    if (argc != 2) {
        cout << "No files or too many files were given." << '\n';
        exit(1);
    }
    string fileName = argv[1];
    vector<string> input = fileReader(fileName);
    vector<Customer*> customers = processInput(input);
    OperatingSystem OS (customers);
    OS.runOS();
    return 0;
}
