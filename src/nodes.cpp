//1b: Bartoszewski (406690), Gajek (400365), Gąsior (407326), Kowalczyk (406185)
#include "nodes.hpp"
#include <map>

void ReceiverPreferences::add_receiver(IPackageReceiver *r)
{
    preferences_.insert({r, 0.0});
    calculatePropability();
};

void ReceiverPreferences::remove_receiver(IPackageReceiver *r)
{
    preferences_.erase(r);
    calculatePropability();
};

void ReceiverPreferences::calculatePropability()
{
    size_t size = preferences_.size();
    for (const auto &[key, value] : preferences_)
    {
        preferences_[key] = 1.0 / float(size);
    }
};

void Worker::do_work(Time time)
{
    if(not buffer_queue && not q_->empty()){
        buffer_queue = q_->pop();
        work_start_time = time;
    }

    if(buffer_queue) {
        if(pd_ - 1  == work_start_time - time){
            push_package(std::move(buffer_queue.value()));
            buffer_queue = std::nullopt;
        }
    }
}

//mapa = {adres1:0.33, adres2:0.33,adres3:0.33}
//maps[adres1] -> 0.33
//losowaliczba
//suma = 0
//for item in  map:
//suma += item
//  losowaliczba < suma
//    return item
//
IPackageReceiver *ReceiverPreferences::choose_receiver()
{

    //    std::map<std::string, int> receiver_pref = {
    //            {"adres1", 0.25},
    //            {"adres2", 0.5},
    //            {"adres3", 0.25}
    //    };

    double losowaliczba = pg_(); //generuje losowa liczbe z przedzialu (0,1)
    double suma = 0;
    std::map<std::string, int>::iterator item;

    for (const auto &[key, value] : preferences_)
    {
        if (losowaliczba < suma)
        {
            suma += value;
        }
        if (losowaliczba > suma)
        {
            return key;
        }
    }
    return preferences_.rbegin()->first;
};

void Ramp::deliver_goods(Time t)
{
    //    if (di_ == 1){
    //        push_package(Package());
    //    }

    if (t % di_ == 0)
    {
        push_package(Package());
    }
}

void PackageSender::send_package(){
    if(sending_buffer_ != std::nullopt){
        receiver_preferences_.choose_receiver()->receive_package(std::move(sending_buffer_.value())); //TODO test
        sending_buffer_ = std::nullopt;//TODO sprawdzić czy potrzebne, może move sam to robi czy coś
    }
}

//1b: Bartoszewski (406690), Gajek (400365), Gąsior (407326), Kowalczyk (406185)
