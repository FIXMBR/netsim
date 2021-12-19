#include "package.hpp"

std::set<ElementID> Package::assigned_IDs;
std::set<ElementID> Package::freed_IDs;

//zwraca nowe id
ElementID Package::get_id(){
    if(freed_IDs.empty()){

        return max_id += 1;
    }
    else {
        return *Package::freed_IDs.begin();
    }
}


void if_exist_then_erase(std::set<ElementID>& search, ElementID erase){
    if(search.find(erase) != search.end()) {
        search.erase(erase); //wstawia do kontenera search, wartość eraase jeśli nie znajdzie tej wartości
    }
}

//tutaj trzeba będzie zmienić funkcję tak, że będzie wstawiałą id, jeśli dana wartość nie istnieje
void if_not_exist_then_insert(std::set<ElementID>& search, ElementID erase){
    if(search.find(erase) == search.end()){
        search.insert(erase);
    }
}


Package::~Package() {

    if (id_ != max_id){
        if_exist_then_erase(assigned_IDs, id_);
        if_not_exist_then_insert(freed_IDs, id_);
    }
}
