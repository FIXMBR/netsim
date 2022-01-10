//1b: Bartoszewski (406690), Gajek (400365), Gąsior (407326), Kowalczyk (406185)
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
    std::for_each(worker_collection_.begin(), worker_collection_.end(), [time](Worker &elem)
                  { elem.do_work(time); });
    //   { elem.do_work(time); });
    //   { dynamic_cast<Worker *>(elem)->do_work(time); });
}

void Factory::do_deliveries(Time time)
{
    std::for_each(ramp_collection_.begin(), ramp_collection_.end(), [time](Ramp &elem)
                  { elem.deliver_goods(time); });
}

void Factory::do_package_passing()
{
    std::for_each(worker_collection_.begin(), worker_collection_.end(), [](Worker &elem)
                  { elem.send_package(); });
    std::for_each(ramp_collection_.begin(), ramp_collection_.end(), [](Ramp &elem)
                  { elem.send_package(); });
}

bool Factory::is_consistent() const
{
    std::map<const PackageSender *, NodeColor> color;
    // std::for_each(worker_collection_.begin(), worker_collection_.end(), [&color](Worker &elem)
    //               { color.insert(
    //                     std::pair<const PackageSender *, NodeColor>(dynamic_cast<PackageSender *>(&elem), NodeColor::UNVISITED)); });
    // std::for_each(ramp_collection_.begin(), ramp_collection_.end(), [&color](Ramp &elem)
    //               { color.insert(
    //                     std::pair<const PackageSender *, NodeColor>(dynamic_cast<PackageSender *>(&elem), NodeColor::UNVISITED)); });

    for (NodeCollection<Worker>::const_iterator it = worker_collection_.begin(); it != worker_collection_.end(); it++)
    {
        color.insert(std::pair<const PackageSender *, NodeColor>(dynamic_cast<const PackageSender *>(&*it), NodeColor::UNVISITED));
    }

    for (NodeCollection<Ramp>::const_iterator it = ramp_collection_.begin(); it != ramp_collection_.end(); it++)
    {
        color.insert(std::pair<const PackageSender *, NodeColor>(dynamic_cast<const PackageSender *>(&*it), NodeColor::UNVISITED));
    }

    //    NodeCollection<Ramp>::iterator it;
    for (auto &ramp : ramp_collection_)
    {
        try
        {
            has_reachable_storehouse(dynamic_cast<const PackageSender *>(&ramp), color);
        }
        catch (std::logic_error &)
        {
            return false;
        }
    }
    return true;
}

bool Factory::has_reachable_storehouse(const PackageSender *sender, std::map<const PackageSender *, NodeColor> &node_colors) const
{
    if (node_colors[sender] == NodeColor::VERIFIED)
        return true;
    node_colors[sender] = NodeColor::VISITED;

     if (sender->receiver_preferences_.get_preferences().empty())
    {
        throw std::logic_error("There is no reciver");
    }
    bool has_other_recivers_than_it = false;

    for (const auto &el : sender->receiver_preferences_.get_preferences())
    {
        if (el.first->get_receiver_type() == ReceiverType::STOREHOUSE)
        {
            has_other_recivers_than_it = true;
        }
        else if (el.first->get_receiver_type() == ReceiverType::WORKER)
        {
            IPackageReceiver *receiver_ptr = el.first;
            auto worker_ptr = dynamic_cast<Worker *>(receiver_ptr);
            auto sendrecv_ptr = dynamic_cast<PackageSender *>(worker_ptr);
            if (sendrecv_ptr == sender)
            {
                continue;
            }
            has_other_recivers_than_it = true;
            if (node_colors[sendrecv_ptr] == NodeColor::UNVISITED)
            {
                has_reachable_storehouse(sendrecv_ptr, node_colors);
            }
        }
    }
    node_colors[sender] = NodeColor::VERIFIED;
    if (has_other_recivers_than_it)
        return true;
    else
        throw std::logic_error("There is no reciver");
}
//1b: Bartoszewski (406690), Gajek (400365), Gąsior (407326), Kowalczyk (406185)