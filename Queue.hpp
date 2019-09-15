#ifndef QUEUE_H
#define QUEUE_H

#include "Customer.hpp"
#include <iostream>

class Queue {
private:
    std::vector<std::vector<Customer*>> priority_queue;
public:
    Queue() {
        //creates a new vector for each priority
        std::vector<Customer*> empty;
        for (int i = 0; i < 7; i++) {
            priority_queue.push_back(empty);
        }
    }

    Queue(std::vector<Customer*> customers)
    {
        //creates a new vector for each priority
        std::vector<Customer*> empty;
        for (int i = 0; i < 7; i++)
        {
            priority_queue.push_back(empty);
        }

        //adds customers to the priority queue based on their priority
        //doesn't care for arrival time at the moment
        for (int i = 0; i < customers.size(); i++)
        {
            priority_queue[customers[i]->getPriority()-1].push_back(customers[i]);
        }
    }

    //Adds a single customer to the priority Queue
    void addCustomer(Customer* customer)
    {
        priority_queue[customer->getPriority()-1].push_back(customer);
    }

    //Adds multiple customers to the priority queue
    void addCustomers (std::vector<Customer*> customer)
    {
        for (int i = 0; i < customers.size(); i++) {
            priority_queue[customers[i]->getPriority()-1].push_back(customers[i]);
        }
    }

    //prints the name and priority of everything in the queue
    void printQueue()
    {
        for (int i = 0; i < priority_queue.size(); i++)
        {
            for (int j = 0; j < priority_queue[i].size(); j++)
            {
                std::cout << priority_queue[i][j]->getName() << ' ';
                std::cout << priority_queue[i][j]->getPriority() << '\n';
                //std::cout << i << '\n';
            }
        }
    }

    //calculates the length of time a customer can spend in the CPU
    int weightedTimeCalc(bool queueNumber)
    {
        int weightedTimeQuantum;
        // Weighted Time Formula Q1
        // ((8 − C's Priority No.) × 10 time units)

        // If false Queue 1
        if (!queueNumber)
        {
            // Priority 1
            if (priority_queue[0].size() > 0)
            {
                weightedTimeQuantum = 70;
            }
            // Priority 2
            else if (priority_queue[1].size() > 0)
            {
                weightedTimeQuantum = 60;
            }
            // Priority 3
            else if (priority_queue[2].size() > 0)
            {
                weightedTimeQuantum = 50;
            }
        }

        // If true Queue 2
        else
        {
            weightedTimeQuantum = 100;
        }
        return weightedTimeQuantum;
    }

    // Increments all elements age within Queue 2
    void ageMechanismQ2()
    {
        for (int i = 0; i < priority_queue.size(); i++)
        {
            for (int j = 0; j < priority_queue[i].size(); j++)
            {
                // Increments the age of each element
                priority_queue[i][j] -> increaseAge();
            }
        }
    }

    // Given priority specified, pop from the start; places at end
    void moveEndQueue(int pre)
    {
        // Places at end of queue
        priority_queue[pre-1].push_back(priority_queue[pre-1][0]);
        // Removes from front of queue
        priority_queue[pre-1].erase(priority_queue[pre-1].begin());
    }

    // Given priority specified, pop from the specified; places at new priority
    void priorityShift(int prevPri, int newPri)
    {
        // Places at end of queue
        priority_queue[newPri-1].push_back(priority_queue[prevPri-1][0]);
        // Removes from front of queue
        priority_queue[prevPri-1].erase(priority_queue[prevPri-1].begin());
    }

    //Destructor - cleans up memory
    ~Queue()
    {
        for (int i = 0; i < priority_queue.size(); i++)
        {
            for (int j = 0; j < priority_queue[i].size(); j++)
            {
                delete priority_queue[i][j];
            }
        }
    }
};

#endif
