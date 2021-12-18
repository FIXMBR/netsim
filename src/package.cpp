#include "package.hpp"

void if_exist_then_erase(std::set<ElementID>& search, ElementID erase){
    if(search.find(erase) != search.end()){
        search.insert(erase); //wstawia do kontenera search, wartość eraase jeśli nie znajdzie tej wartości
    }
}

//tutaj trzeba będzie zmienić funkcję tak, że będzie wstawiałą id, jeśli dana wartość nie istnieje
void if_not_exist_then_insert(std::set<ElementID>& search, ElementID erase){
    if(search.find(erase) == search.end()){
        search.insert(erase);
    }
}