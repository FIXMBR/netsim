//1b: Bartoszewski (406690), Gajek (400365), Gąsior (407326), Kowalczyk (406185)
#include "nodes.hpp"
#include<map>

void ReceiverPreferences::add_receiver(IPackageReceiver *r) {
    preferences_.insert({r,0.0});
    calculatePropability();
};

void ReceiverPreferences::remove_receiver(IPackageReceiver *r) {
    preferences_.erase(r);
    calculatePropability();
};

void ReceiverPreferences::calculatePropability() {
    size_t size =  preferences_.size();
    for (const auto& [key, value] : preferences_) {
        preferences_[key] = 1/size;
    }
};




//mapa = {adres1:0.33, adres2:0.33,adres3:0.33}
//maps[adres1] -> 0.33
//losowaliczba
//suma = 0
//for item in  map:
//suma += item
//  losowaliczba < suma
//    return item
//
IPackageReceiver * ReceiverPreferences::choose_receiver(){

    std::map<std::string, int> receiver_pref = {
            {"adres1", 0.33},
            {"adres2", 0.33},
            {"adres3", 0.33}
    };

    double losowaliczba = rand() % 1;  //generuje losowa liczbe z przedzialu (0,1)
    double suma = 0;
    std::map<std::string, int>::iterator item;

    for (item = receiver_pref.begin(); item != receiver_pref.end(); item++) {
        if (losowaliczba < suma) {
            suma += 0.33;
        }
        if (losowaliczba > suma) {
            return item->first ;
        }
    }

};

void Ramp::deliver_goods(Time t) {
    if (timeOffset_ == 1){
        push_package(Package());
    }
    else{
        if (t % timeOffset_ == 1) {
            push_package(Package());
        }
    }
}

//1b: Bartoszewski (406690), Gajek (400365), Gąsior (407326), Kowalczyk (406185)
