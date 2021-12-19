#ifndef NETSIM_PACKAGE_HPP
#define NETSIM_PACKAGE_HPP

#include <vector>
#include <iostream>
#include <set>
#include "types.hpp"


class Package{
private:
    static std::set<ElementID> assigned_IDs; //przechowywać będzie przydzielone obecnie ID
    static std::set<ElementID> freed_IDs; //przechowywać będzie ID kiedyś użyte, ale obecnie zwolnione
    ElementID max_id = 0;
    ElementID id_ = max_id;

public:
    Package();
    Package(const Package&) = delete;
    ElementID get_id();
    ~Package();
};


#endif //NETSIM_PACKAGE_HPP