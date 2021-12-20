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
