//1b: Bartoszewski (406690), Gajek (400365), Gąsior (407326), Kowalczyk (406185)
#ifndef NETSIM_PACKAGE_HPP
#define NETSIM_PACKAGE_HPP

#include <vector>
#include <iostream>
#include <set>
#include "types.hpp"

class Package
{
private:
    static std::set<ElementID> assigned_IDs; //przechowywać będzie przydzielone obecnie ID
    static std::set<ElementID> freed_IDs;    //przechowywać będzie ID kiedyś użyte, ale obecnie zwolnione
    ElementID id_;

public:
    Package();
    Package &operator=(Package &&p) = default;
    Package(int x) { id_ = x; };
    Package(const Package &p) { id_ = p.get_id(); };
    Package(Package &&p) = default;
    ElementID get_id() const { return id_; };
    ~Package();
};

#endif //NETSIM_PACKAGE_HPP
//1b: Bartoszewski (406690), Gajek (400365), Gąsior (407326), Kowalczyk (406185)