#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>

class Customer
{
private:
    std::string name;
    int arrivalTime;
    int age;
    int priority;
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
        totalRunTime = 5*tickets;
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
    int getarrivalTime()
    {
        return arrivalTime;
    }

    //priority
    int getPriority()
    {
        return priority;
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

    //OTHER USEFUL FUNCTIONS
    //increases age by 1
    void increaseAge()
    {
        age++;
    }

    //Priority promotion and demotion
    void promote()
    {
        priority++;
    }
    void demote()
    {
        priority--;
    }
};

#endif
