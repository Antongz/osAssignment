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
    ~OperatingSystem();
};


#endif
