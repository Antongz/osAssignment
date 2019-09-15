#ifndef OPERATING_SYSTEM
#define OPERATING_SYSTEM

#include <algorithm>
#include <vector>
#include "Queue.hpp"
#include "Customer.hpp"

class OperatingSystem
{
private:
    //Comparison function
    bool sortByArrivalTime(Customer* C1, Customer* C2)
    {
        return (C1->getarrivalTime() < C2->getarrivalTime());
    }

    std::vector<Customer*> customers;
    Queue priority_queue;
public:
    OperatingSystem(std::vector<Customer*> input)
    {
        //sorts the customers by arrival time
        customers = input;
        std::stable_sort(customers.begin(),customers.end(),sortByArrivalTime);

        //places all the customers with arrival
        for (int i = 0; i < customers.size(); i++)
        {
            //adds customers with zero arrival time
            if (customers[i]->getarrivalTime == 0)
            {
                priority_queue.addCustomer(customer[i])
            }
            //removes all customers with 0 arrival time
            else
            {
                customers.erase(customers.begin(),customer.begin()+i);
                break;
            }
        }
    }
    
    
    
    // Prints all customer details according to scheduling
    void printSchedule(vector<vector<string>> input) {
        // First Line Output
        cout << "name   arrival   end   ready   running   waiting" << endl;
        for (int i = 0; i < input.size(); i++) {
            for (int j = 0; j < 6; j++) {
                // Name
                if (j == 0) {
                    cout << input[i][j];
                    continue;
                }
                // Spaces needed
                for (int g = 0; g < (10 - input[i][j].length();); g++) {
                    cout << " ";
                }
                // Following inputiables
                cout << input[i][j];
            }
            cout << endl;
        }
    }

    ~OperatingSystem();
};


#endif
