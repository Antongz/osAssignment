#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>

class Customer
{
private:
    std::string name;
    int arrivelTime;
    int age;
    int priority;
    int beginTime;
    int endTime;
    int totalRunTime;
public:
    //i = input
    //Constructor
    Customer(std::string iName, int iArrivelTime, int iPriority, int iAge, int tickets)
    {
        name = iName;
        arrivelTime = iArrivelTime;
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

    //arrivelTime;
    int getArrivelTime()
    {
        return arrivelTime;
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
