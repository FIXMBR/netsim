#include "factory.hpp"


//void Factory::remove_receiver(NodeCollection<Node>& collection,  ElementID id){
//    NodeCollection<Node>::iterator sender = collection.find_by_id(id);
//    for (auto const& node : collection) {
//        node.receiver_preferences_.remove_receiver(sender);
//    }
//};


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
bool has_reachable_storehouse(const PackageSender* sender, std::map<const PackageSender*, NodeColor>& node_colors){
    if(node_colors[sender] == NodeColor::VERIFIED)
        return true;
    node_colors[sender] = NodeColor::VISITED;

}

bool Factory::is_consistent();