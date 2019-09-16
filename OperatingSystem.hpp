//Rory Martin a1740203
//William Godfrey a1743033

#ifndef OPERATING_SYSTEM
#define OPERATING_SYSTEM

#include <algorithm>
#include <vector>
#include <string>
#include <iostream>
#include "Queue.hpp"
#include "Customer.hpp"

class OperatingSystem
{
private:
    //Comparison function
    static bool sortByArrivalTime(Customer* C1, Customer* C2)
    {
        return (C1->getArrivalTime() < C2->getArrivalTime());
    }
    std::vector<Customer*> customers;
    Queue priority_queue;
    int current_time;
    std::vector<Customer*> output;
    Customer* Q1Head;
    Customer* Q2Head;
public:
    OperatingSystem(std::vector<Customer*> input)
    {
        //sorts the customers by arrival time
        current_time = 0;
        customers = input;
        std::stable_sort(customers.begin(),customers.end(),sortByArrivalTime);

        //places all the customers with arrival
        for (int i = 0; i < customers.size(); i++)
        {
            //adds customers with zero arrival time
            if (customers[i]->getArrivalTime() == 0)
            {
                priority_queue.addCustomer(customers[i]);
            }
            //removes all customers with 0 arrival time
            else
            {
                customers.erase(customers.begin(),customers.begin()+i);
                break;
            }
        }

        //Case if all arrival times are 0
        if (customers[customers.size()-1]->getArrivalTime() == 0)
        {
            customers.clear();
        }

        //Assigns the heads of the Queues
        Q1Head = priority_queue.findQ1Head();
        Q2Head = priority_queue.findQ2Head();
    }

    //calculates the length of time a customer can spend in the CPU
    int weightedTimeCalc(bool Q1Active)
    {
        int weightedTimeQuantum;
        int ticketQuota = 20;
        // Weighted Time Formula Q1
        // ((8 − C's Priority No.) × 10 time units)

        // If true Queue 1 is active
        if (Q1Active)
        {
            ticketQuota = (8-Q1Head->getPriority())*2;
            //Checks if the customer has less tickets than their allowed quota
            if (Q1Head->getRemainingTickets() < ticketQuota)
            {
                weightedTimeQuantum = 5*Q1Head->getRemainingTickets();
            }
            else
            {
                weightedTimeQuantum = (8-Q1Head->getPriority())*10;
            }
        }

        // If  false Queue 2 is active
        else
        {
            //Checks if the customer has less tickets than their allowed quota
            if (Q2Head->getRemainingTickets() < ticketQuota)
            {
                weightedTimeQuantum = 5*Q2Head->getRemainingTickets();
            }
            else
            {
                weightedTimeQuantum = 100;
            }
        }
        return weightedTimeQuantum;
    }

    void runCPUIteration()
    {
        //Checks if there is anything in Queue 1
        if (Q1Head != nullptr)
        {
            //checks if the customer has been assigned a beginTime
            if (Q1Head->getBeginTime() == -1)
            {
                Q1Head->setBeginTime(current_time);
            }
            //decreases tickets and increases CPU time
            current_time += weightedTimeCalc(true);
            Q1Head->decreaseTickets((8-Q1Head->getPriority())*2);

            //ages Queue 2
            priority_queue.ageMechanismQ2();
            //checks if all the tickets have been completed
            if (Q1Head->getRemainingTickets() <= 0)
            {
                //sets the customers endTime and removes the customer from the queue
                Q1Head->setEndTime(current_time);
                output.push_back(Q1Head);
                priority_queue.removeFromQueue(Q1Head->getPriority());
            }
            else
            {
                Q1Head->increaseAge();
                //checks if customer has had three runs at their current priority
                if (Q1Head->getAge() == 3)
                {
                    Q1Head->resetAge();
                    //customer demoted in priority
                    priority_queue.priorityShift(Q1Head->getPriority(),Q1Head->getPriority()+1);
                    Q1Head->demote();
                }
                else
                {
                    priority_queue.moveEndQueue(Q1Head->getPriority());
                }
            }
        }
        //If Queue 1 empty and Queue 2 not
        else if (Q2Head != nullptr)
        {
            //checks if the customer has been assigned a beginTime
            if (Q2Head->getBeginTime() == -1)
            {
                Q2Head->setBeginTime(current_time);
            }
            //accounting for interrupts, increases CPU time and decreases tickets
            bool interrupt = false;
            int originalTime = current_time;
            current_time += weightedTimeCalc(false);
            int actualRunTime = checkForInteruptAndArrivals(originalTime);
            //checks for an interrupt before tickets are decreased as weightedTimeCalc
            // is dependent on the number of tickets;
            if (actualRunTime < weightedTimeCalc(false))
            {
                interrupt = true;
            }
            Q2Head->decreaseTickets(actualRunTime/5);

            //Ages queue 2
            priority_queue.ageMechanismQ2();
            //if interrupt occurs, Q2 head not changed
            if (interrupt)
            {
                Q2Head->decreaseAge();
            }
            //checks if all the tickets have been completed
            else if (Q2Head->getRemainingTickets() <= 0)
            {
                Q2Head->setEndTime(current_time);
                output.push_back(Q2Head);
                priority_queue.removeFromQueue(4);
            }
            else
            {
                Q2Head->decreaseAge();
                priority_queue.moveEndQueue(4);
            }
        }
    }

    //Looks for new arrivals at or below the current time if any exist
    int checkForInteruptAndArrivals(int original_time)
    {
        int TimeQuota = current_time - original_time;
        while (!customers.empty() && customers[0]->getArrivalTime() < current_time)
        {
            //Checks if interrupt occurs => if so initiate Shit Bricks
            if (customers[0]->getPriority() < 4)
            {
                current_time = customers[0]->getArrivalTime();
            }

            // Adds new arrival to the prirorty queue & removes start from customer
            priority_queue.addCustomer(customers[0]);
            customers.erase(customers.begin());

            //Shit Bricks
            if (current_time - original_time < TimeQuota)
            {
                current_time -= current_time % 5;
                return (current_time - original_time);
            }
        }

        return TimeQuota;
    }

    void checkForArrivals()
    {
        while (!customers.empty() && customers[0]->getArrivalTime() <= current_time)
        {
            // Adds new arrival to the prirorty queue & removes start from customer
            priority_queue.addCustomer(customers[0]);
            customers.erase(customers.begin());
        }
    }

    // Prepares all member variables and assigns them to a 2-Dimensional Vector
    std::vector<std::vector<std::string>> schedulePrep()
    {
        int size = output.size();
        std::vector<std::vector<std::string>> returnVec;

        for (int i = 0; i < size; i++) {
            // Assigning Values
            std::vector<std::string> verticalVec(6);
            returnVec.push_back(verticalVec);
            returnVec[i][0] = output[i]->getName(); // Name
            returnVec[i][1] = std::to_string(output[i]->getArrivalTime()); // Arrival
            returnVec[i][2] = std::to_string(output[i]->getEndTime()); // End
            returnVec[i][3] = std::to_string(output[i]->getBeginTime()); // Ready
            returnVec[i][4] = std::to_string(output[i]->getTotalRun()); // Running
            returnVec[i][5] = std::to_string(output[i]->getEndTime()-output[i]->getBeginTime()-output[i]->getTotalRun()); // Waiting
        }

        return returnVec;
    }

    // Prints all customer details according to scheduling
    void printSchedule(std::vector<std::vector<std::string>> input)
    {
        // First Line Output
        std::cout << "name   arrival   end   ready   running   waiting" << std::endl;
        for (int i = 0; i < input.size(); i++)
        {
            for (int j = 0; j < 6; j++)
            {
                // Name
                if (j == 0)
                {
                    std::cout << input[i][j];
                    continue;
                }
                // Spaces needed
                for (int g = 0; g < (10 - input[i][j].length()); g++)
                {
                    std::cout << " ";
                }
                // Following inputiables
                std::cout << input[i][j];
            }
            std::cout << std::endl;
        }
    }

    void runOS()
    {
        while (Q1Head != nullptr || Q2Head != nullptr)
        {
            runCPUIteration();
            priority_queue.checkForPromotionQ2();
            Q2Head = priority_queue.findQ2Head();
            checkForArrivals();
            Q1Head = priority_queue.findQ1Head();

            //checks for customers arriving after queue is empty
            if (Q1Head == nullptr && Q2Head == nullptr && !customers.empty())
            {
                //checks which queue the customer belongs in
                if (customers[0]->getPriority() <= 3)
                {
                    Q1Head = customers[0];
                }
                else
                {
                    Q2Head = customers[0];
                }
                priority_queue.addCustomer(customers[0]);
                customers.erase(customers.begin());
            }
        }
        printSchedule(schedulePrep());
    }

    ~OperatingSystem()
    {
        for (int i = 0; i < output.size(); i++)
        {
            delete output[i];
        }
    }
};


#endif
