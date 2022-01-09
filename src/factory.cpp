#include "factory.hpp"

void Factory::remove_receiver(collection: NodeCollection<Node>&, id: ElementID){
    NodeCollection<Node>::iterator sender = collection.find_by_id(id);
    for (auto const& node : collection) {
        node.receiver_preferences_.remove_receiver(sender);
    }
};

void Factory::do_work(Time time)
{
std::for_each(worker_collection_.begin(), worker_collection_.end(), (auto elem){elem.do_work(time);});
}

void Factory::do_deliveries(Time time)
{
    std::for_each(ramp_collection_.begin(), ramp_collection_.end(), (auto elem){elem.deliver_goods(time);});
}

void Factory::do_package_passing(Time time)
{

}