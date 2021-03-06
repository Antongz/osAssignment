//Rory Martin a1740203
//William Godfrey a1743033

#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <algorithm>
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include <cstddef>

class Customer
{
private:
    std::string name;
    int arrivalTime;
    int age;
    int priority;
    int ticketsRemaining;
    int beginTime;
    int endTime;
    int totalRunTime;
public:
    //i = input
    //Constructor
    Customer(std::string iName, int iarrivalTime, int iPriority, int iAge, int tickets)
    {
        name = iName;
        arrivalTime = iarrivalTime;
        priority = iPriority;
        age = iAge;
        ticketsRemaining = tickets;
        totalRunTime = 5*tickets;
        beginTime = -1;
    }

    ~Customer()
    {

    }
    // GETTERS AND SETTERS (only relevant ones)
    //name
    std::string getName()
    {
        return name;
    }

    //arrivalTime;
    int getArrivalTime()
    {
        return arrivalTime;
    }

    //priority
    int getPriority()
    {
        return priority;
    }

    //age
    int getAge()
    {
        return age;
    }

    //ticketsRemaining
    int getRemainingTickets()
    {
        return ticketsRemaining;
    }

    //beginTime
    void setBeginTime(int begin)
    {
        beginTime = begin;
    }
    int getBeginTime()
    {
        return beginTime;
    }

    //endTime
    void setEndTime(int end)
    {
        endTime = end;
    }
    int getEndTime()
    {
        return endTime;
    }

    //totalRunTime
    int getTotalRun()
    {
        return totalRunTime;
    }

    //OTHER USEFUL FUNCTIONS
    //increases age by 1
    void increaseAge()
    {
        age++;
    }
    //decrease age by 1
    void decreaseAge()
    {
        age--;
    }
    //sets age to zero
    void resetAge()
    {
        age = 0;
    }

    //Priority promotion and demotion
    void demote()
    {
        priority++;
    }
    void promote()
    {
        priority--;
    }

    //Decrease No. tickets
    void decreaseTickets(int n)
    {
        ticketsRemaining -= n;
    }
};

#endif
