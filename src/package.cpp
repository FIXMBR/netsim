//1b: Bartoszewski (406690), Gajek (400365), Gąsior (407326), Kowalczyk (406185)
#include "package.hpp"

std::set<ElementID> Package::assigned_IDs;
std::set<ElementID> Package::freed_IDs;

//zwraca nowe id
ElementID Package::get_id() const {
    return id_;
}


Package::~Package()
{
    assigned_IDs.erase(id_);
    freed_IDs.insert(id_);
}
//1b: Bartoszewski (406690), Gajek (400365), Gąsior (407326), Kowalczyk (406185)