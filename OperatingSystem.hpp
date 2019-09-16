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
            if (customers[i]->getarrivalTime() == 0)
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
            ticketQuota = (Q1Head->getPriority())*2;
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

            //checks if all the tickets have been completed
            if (Q1Head->getRemainingTickets() <= 0)
            {
                Q1Head->setEndTime(current_time);
                output.push_back(Q1Head);
                priority_queue.removeFromQueue(Q1Head->getPriority());
                Q1Headpriority_queue.findQ1Head();
            }
            else
            {
                Q1Head->increaseAge();
                priority_queue.ageMechanismQ2();
                //checks if customer has had three runs at their current priority
                if (Q1Head->getAge() == 3)
                {
                    Q1Head->resetAge();
                    //checks if customer need to be shifted to queue 2 upon demotion
                    if (Q1Head->getPriority() == 3)
                    {
                        //customer demoted to queue 2
                        priority_queue.queueShift();
                        Q1Head->demote();
                    }
                    else
                    {
                        //customer demoted in priority
                        priority_queue.priorityShift(Q1Head->getPriority(),Q1Head->getPriority()+1);
                        Q1Head->demote();
                    }
                }
                else
                {
                    priority_queue.moveEndQueue(Q1Head->getPriority());
                }
            }
        }
        //If Queue
        else if (Q2Head != nullptr)
        {
            //checks if the customer has been assigned a beginTime
            if (Q2Head->getBeginTime() == -1)
            {
                Q2Head->setBeginTime(current_time);
            }

            //ADD check to see whether customer gets interupted;

            //decreases tickets and increases CPU time
            current_time += weightedTimeCalc(false);
            Q2Head->decreaseTickets(20);

            //checks if all the tickets have been completed
            if (Q2Head->getRemainingTickets() <= 0)
            {
                Q2Head->setEndTime(current_time);
                output.push_back(Q1Head);
                priority_queue.removeFromQueue(Q1Head->getPriority());
                priority_queue.findQ1Head();
            }
            else
            {
                Q1Head->increaseAge();
                priority_queue.ageMechanismQ2();
                //check if priority need to be decreased -> if statement
                priority_queue.moveEndQueue(Q1Head->getPriority());
            }
        }
    }

    void runOS()
    {

        //Find Q2 head
        //check for arrivals
        //Find Q1 head
    }

    // Prepares all member variables and assigns them to a 2-Dimensional Vector
    vector<vector<string>> schedulePrep(vector<Customer*> Customers) {
        int size = Customers.size();
        vector<vector<string>> returnVec;

        for (int i = 0; i < size; i++) {
            // Assigning Values
            vector<string> verticalVec(6);
            returnVec.push_back(verticalVec);
            returnVec[i][0] = stoi(getName()); // Name
            returnVec[i][1] = stoi(getarrivalTime()); // Arrival
            returnVec[i][2] = stoi(getEndTime()); // End
            returnVec[i][3] = stoi(getBeginTime()); // Ready
            returnVec[i][4] = stoi(getTotalRun()); // Running
            returnVec[i][5] = stoi((getEndTime()-getBeginTime()-getTotalRun()); // Waiting
        }
        return returnVec;
    }

    // Prints all customer details according to scheduling
    void printSchedule(vector<vector<string>> input)
    {
        // First Line Output
        cout << "name   arrival   end   ready   running   waiting" << endl;
        for (int i = 0; i < input.size(); i++)
        {
            for (int j = 0; j < 6; j++)
            {
                // Name
                if (j == 0)
                {
                    cout << input[i][j];
                    continue;
                }
                // Spaces needed
                for (int g = 0; g < (10 - input[i][j].length()); g++)
                {
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
