#include "factory.hpp"


//template <class Node> void Factory::remove_receiver(NodeCollection<Node>& collection,  ElementID id){
//
//    typename NodeCollection<Node>::iterator receiver = collection.find_by_id(id);
////        IPackageReceiver& receiver = collection.find_by_id(id);
//
//    for (auto& node : worker_collection_) {
//        node.receiver_preferences_.remove_receiver(&*receiver);
//    }
//    for (auto& node : ramp_collection_) {
//        node.receiver_preferences_.remove_receiver(&*receiver);
//    }
//
//    collection.remove_by_id(id);
//}


void Factory::do_work(Time time)
{
    std::for_each(worker_collection_.begin(), worker_collection_.end(), [time](auto elem){elem.do_work(time);});
}


void Factory::do_deliveries(Time time)
{
    std::for_each(ramp_collection_.begin(), ramp_collection_.end(), [time](auto elem){elem.deliver_goods(time);});
}

void Factory::do_package_passing()
{
    std::for_each(worker_collection_.begin(), worker_collection_.end(), [](auto elem){elem.send_package(time);});
    std::for_each(ramp_collection_.begin(), ramp_collection_.end(), [](auto elem){elem.send_package(time);});
}

enum class NodeColor { UNVISITED, VISITED, VERIFIED };

bool Factory::is_consistent() const {
    kolor = 
}

bool has_reachable_storehouse(const PackageSender* sender, std::map<const PackageSender*, NodeColor>& node_colors){
    if(node_colors[sender] == NodeColor::VERIFIED)
        return true;
    node_colors[sender] = NodeColor::VISITED;

//    jeśli `nadawca` nie ma zdefiniowanych odbiorców: //FIXME Ktoś ma jakiś pomysł?
    if(sender->receiver_preferences_.get_preferences().empty()){
        throw std::logic_error("There is no reciver");
    }
    bool has_other_recivers_than_it = false;
//    for(jeśli typ odbiorcy to MAGAZYN): //FIXME Ktoś ma jakiś pomysł?
    for(const auto& el:sender->receiver_preferences_.get_preferences()){
        if(el.first -> get_receiver_type() == ReceiverType::STOREHOUSE) {
            has_other_recivers_than_it = true;
        }
        else if(el.first -> get_receiver_type() == ReceiverType::WORKER) {
            IPackageReceiver* receiver_ptr = el.first ;
            auto worker_ptr = dynamic_cast<Worker*>(receiver_ptr);
            auto sendrecv_ptr = dynamic_cast<PackageSender*>(worker_ptr);
            if(sendrecv_ptr==sender){
                continue;
            }
            has_other_recivers_than_it = true;
            if(node_colors[sendrecv_ptr]==NodeColor::UNVISITED){
                has_reachable_storehouse(sendrecv_ptr,node_colors);
            }
        }
    }
    node_colors[sender] = NodeColor::VERIFIED;
    if(has_other_recivers_than_it)
        return true;
    else
        throw std::logic_error("There is no reciver");
}

