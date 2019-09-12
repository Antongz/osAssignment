#ifndef QUEUE_H
#define QUEUE_H

#include "Customer.hpp"
#include <iostream>

class Queue
{
private:
    std::vector<std::vector<Customer*>> priority_queue;
public:
    Queue()
    {
        //creates a new vector for each priority
        std::vector<Customer*> empty;
        for (int i = 0; i < 7; i++)
        {
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
        //doesn't care for arrivel time at the moment
        for (int i = 0; i < customers.size(); i++)
        {
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
