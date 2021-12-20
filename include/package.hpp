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
    Package(){
        if(freed_IDs.empty()){
            if(!assigned_IDs.empty()){
                ElementID max_id = *assigned_IDs.rbegin();
                id_ = max_id + 1;
                assigned_IDs.insert(id_);
            }
            else{
                id_ = 1;
                assigned_IDs.insert(id_);
            }
        }
        else {
            id_ = *freed_IDs.begin();
            assigned_IDs.insert(id_);
            freed_IDs.erase(id_);
        }
    };

    Package(int x){id_ = x;};
    Package(const Package &p) { id_ = p.get_id(); };
    ElementID get_id() const;
    ~Package();
};

#endif //NETSIM_PACKAGE_HPP