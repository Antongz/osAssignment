#ifndef OPERATING_SYSTEM
#define OPERATING_SYSTEM

#include <algorithm>

class OperatingSystem
{
private:
    bool comparison(Customer* C1, Customer* C2)
    {
        return (C1->getArrivelTime() < C2->getArrivelTime());
    }
    sortByArrivalTime(std::vector<Customer*> customers)
    {
        std::stable_sort(customers.begin(),customer.end(),comparison)
    }
public:
    OperatingSystem(std::vector<Customer*> customers)
    {
        sortByArrivalTime(customers);
    }
    ~OperatingSystem();
};


#endif
