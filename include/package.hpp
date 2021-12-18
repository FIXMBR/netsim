#ifndef NETSIM_PACKAGE_HPP
#define NETSIM_PACKAGE_HPP

#include <vector>
#include <iostream>
#include <set>
#include "types.hpp"

using id_t = int; //typ ElementID

class Package{
private:
    static std::set<ElementID> assigned_IDs; //przechowywać będzie przydzielone obecnie ID
    static std::set<ElementID> freed_IDs; //przechowywać będzie ID kiedyś użyte, ale obecnie zwolnione

public:
    Package();
    Package(id_t i = 0): ElementID(i) {}; //trzeba zmienić w zależności od sposobu wyznaczania ID
    Package(Package &&) noexcept;
    Package(const Package&) = delete;
    id_t get_id() const; //czy tutaj trzeba to
    ~Package();
};


#endif //NETSIM_PACKAGE_HPP