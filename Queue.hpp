//Rory Martin a1740203
//William Godfrey a1743033

#ifndef QUEUE_H
#define QUEUE_H

#include "Customer.hpp"
#include <algorithm>
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include <cstddef>

class Queue {
private:
    std::vector<std::vector<Customer*> > priority_queue;
public:
    Queue() {
        //creates a new vector for each priority
        std::vector<Customer*> empty;
        for (int i = 0; i < 4; i++)
        {
            priority_queue.push_back(empty);
        }
    }

    Queue(std::vector<Customer*> customers)
    {
        //creates a new vector for each priority
        std::vector<Customer*> empty;
        for (int i = 0; i < 4; i++)
        {
            priority_queue.push_back(empty);
        }

        //adds customers to the priority queue based on their priority
        //doesn't care for arrival time at the moment
        for (int i = 0; i < customers.size(); i++)
        {
            if (customers[i]->getPriority() <= 3)
            {
                priority_queue[customers[i]->getPriority()-1].push_back(customers[i]);
            }
            else
            {
                priority_queue[3].push_back(customers[i]);
            }
        }
    }

    //Adds a single customer to the priority Queue
    void addCustomer(Customer* customer)
    {
        if (customer->getPriority() <= 3)
        {
            priority_queue[customer->getPriority()-1].push_back(customer);
        }
        else
        {
            priority_queue[3].push_back(customer);
        }
    }

    //Adds multiple customers to the priority queue
    void addCustomers (std::vector<Customer*> customers)
    {
        for (int i = 0; i < customers.size(); i++)
        {
            if (customers[i]->getPriority() <= 3)
            {
                priority_queue[customers[i]->getPriority()-1].push_back(customers[i]);
            }
            else
            {
                priority_queue[3].push_back(customers[i]);
            }
        }
    }

    //Finds the head element of Queue 1
    Customer* findQ1Head()
    {
        for (int i = 0; i < 3; i++)
        {
            if (!priority_queue[i].empty())
            {
                return priority_queue[i][0];
            }
        }

        return NULL;
    }

    //Finds the head element of Queue 2
    Customer* findQ2Head()
    {
        if (!priority_queue[3].empty())
        {
            return priority_queue[3][0];
        }
        return NULL;
    }

    //prints the name and priority of everything in the queue
    void printQueue()
    {
        std::cout << "queue 1: " << '\n';
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < priority_queue[i].size(); j++)
            {
                std::cout << priority_queue[i][j]->getName() << '\t';
                std::cout << priority_queue[i][j]->getArrivalTime() << '\t';
                std::cout << priority_queue[i][j]->getRemainingTickets() << '\t';
                std::cout << priority_queue[i][j]->getPriority() << '\t';
                std::cout << priority_queue[i][j]->getAge() << '\t';
                std::cout << '\n';
            }
        }
        std::cout << "queue 2:" << '\n';
        for (int j = 0; j < priority_queue[3].size(); j++)
        {
            std::cout << priority_queue[3][j]->getName() << '\t';
            std::cout << priority_queue[3][j]->getArrivalTime() << '\t';
            std::cout << priority_queue[3][j]->getRemainingTickets() << '\t';
            std::cout << priority_queue[3][j]->getPriority() << '\t';
            std::cout << priority_queue[3][j]->getAge() << '\t';
            std::cout << '\n';
        }
    }

    // Increments all elements age within Queue 2
    void ageMechanismQ2()
    {
        for (int j = 0; j < priority_queue[3].size(); j++)
        {
            // Increments the age of each element
            priority_queue[3][j] -> increaseAge();
        }
    }

    // Given priority specified, pop from the start; places at end
    void moveEndQueue(int priority)
    {
        // Places at end of queue
        priority_queue[priority-1].push_back(priority_queue[priority-1][0]);
        // Removes from front of queue
        priority_queue[priority-1].erase(priority_queue[priority-1].begin());
    }

    // Given priority specified, pop from the specified; places at new priority
    void priorityShift(int prevPri, int newPri)
    {
        // Places at end of queue
        priority_queue[newPri-1].push_back(priority_queue[prevPri-1][0]);
        // Removes from front of queue
        priority_queue[prevPri-1].erase(priority_queue[prevPri-1].begin());
    }

    // Given priority specified, pop from the specified; places at new priority
    void queueDemotion()
    {
        // Places at end of queue
        priority_queue[3].insert(priority_queue[3].begin(), priority_queue[2][0]);
        // Removes from front of queue
        priority_queue[2].erase(priority_queue[2].begin());
    }

    //Checks each customer in queue 2 to see if a promotion is warrented
    void checkForPromotionQ2()
    {
        Customer* temp;
        for (int j = 0; j < priority_queue[3].size(); j++)
        {
            //Checks if age has reached 8
            if (priority_queue[3][j]->getAge() == 8)
            {
                temp = priority_queue[3][j];
                temp->resetAge();
                temp->promote();
            }
        }
    }

    //removes element from Queue
    void removeFromQueue(int priority)
    {
        priority_queue[priority-1].erase(priority_queue[priority-1].begin());
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
