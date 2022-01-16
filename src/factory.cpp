//1b: Bartoszewski (406690), Gajek (400365), Gąsior (407326), Kowalczyk (406185)
#include <sstream>
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

ParsedLineData parse_line(const std::string& line) {

    std::vector<std::string> tokens;
    std::string token;

    std::istringstream token_stream(line);
    char delimiter = ' ';

    while (std::getline(token_stream, token, delimiter)) {
    tokens.push_back(token);
    }

    std::string type = reinterpret_cast<const char*>(token.front());
    tokens.erase(tokens.begin());
    ParsedLineData parse = ParsedLineData();
    if(type == "LOADING_RAMP")
        parse.element_type = ElementType::LOADING_RAMP;
    if(type == "WORKER")
        parse.element_type = ElementType::WORKER;
    if(type == "STOREHOUSE")
        parse.element_type = ElementType::STOREHOUSE;
    if(type == "LINK")
        parse.element_type = ElementType::LINK;
    
    for(const auto& el: tokens){
        std::vector<std::string> key_values;
        std::string tag;
        std::istringstream single_token(el);
        char del = '=';
        while(std::getline(single_token, tag, del)){
            key_values.push_back(tag);
        }
        parse.parameters[key_values[0] = key_values[1]];
    }
    return parse;
}

Factory load_factory_structure(std::istream& is){
    Factory factory;
    std::string line;

    while (std::getline(is, line)) {
        if(line[0] == ';' or line.empty())
            continue;
        ParsedLineData parsed_line = parse_line(line);
        if(parsed_line.element_type==ElementType::LOADING_RAMP){
//            LOADING_RAMP id=1 delivery-interval=3
            factory.add_ramp(Ramp(std::stoi(parsed_line.parameters["id"]),std::stoi(parsed_line.parameters["delivery-interval"])));
        }
        else if(parsed_line.element_type ==ElementType::WORKER){
//            WORKER id=1 processing-time=2 queue-type=FIFO
            PackageQueueType q;
            for(const auto &el: parsed_line.parameters){
                if (el.first == "queue-type"){
                    if(el.second == "FIFO")
                        q = PackageQueueType::FIFO;
                    else if (el.second == "LIFO")
                        q = PackageQueueType::LIFO;
                }
            }
            factory.add_worker(Worker(std::stoi(parsed_line.parameters["id"]), std::stoi(parsed_line.parameters["processing-time"]), std::make_unique<PackageQueue>(q)));
        }
        else if(parsed_line.element_type ==ElementType::STOREHOUSE){
//            STOREHOUSE id=1
            factory.add_storehouse(Storehouse(std::stoi(parsed_line.parameters["id"])));
        }
        else if(parsed_line.element_type ==ElementType::LINK){
//            LINK src=ramp-1 dest=worker-1
            size_t pos = parsed_line.parameters["src"].find('-');
            std::string src_type = parsed_line.parameters["src"].substr(0, pos);
            ElementID src_id  = std::stoi(parsed_line.parameters["src"].substr(pos + 1));

            pos = parsed_line.parameters["dest"].find('-');
            std::string dest_type = parsed_line.parameters["dest"].substr(0, pos);
            ElementID dest_id  = std::stoi(parsed_line.parameters["dest"].substr(pos + 1));
            IPackageReceiver* receiver;
            if(dest_type=="worker") {
                receiver=&(*factory.find_worker_by_id(dest_id));
            }else if(dest_type=="store"){
                receiver=&(*factory.find_storehouse_by_id(dest_id));
            }

            if (src_type == "ramp"){
                Ramp& r = *(factory.find_ramp_by_id(src_id));
                r.receiver_preferences_.add_receiver(receiver);
            }else if(src_type == "worker"){
                Worker& r = *(factory.find_worker_by_id(src_id));
                r.receiver_preferences_.add_receiver(receiver);
            }

        }

    }
    return factory;
}

void save_factory_structure(Factory& factory, std::ostream& os){

    if (factory.ramp_cbegin() != factory.ramp_cend()){
        os << "; == LOADING RAMPS ==" << '\n' << '\n';
        for (auto i = factory.ramp_cbegin(); i != factory.ramp_cend(); i++){
            os << "LOADING_RAMP id =" << std::to_string(i->get_id()) << "delivery-interval=" << std::to_string(i->get_delivery_interval()) << '\n';
        }
    }
    if (factory.worker_cbegin() != factory.worker_cend()){
        //.get_queue()->get_queue_type()
        os << "; == WORKERS ==" << '\n' << '\n';
        for (auto i = factory.worker_cbegin(); i != factory.worker_cend(); i++){
            os << "WORKER id =" << std::to_string(i->get_id()) << "processing-time=" << std::to_string(i->get_processing_duration()) <<  "queue-type=" << ((i ->get_queue()->get_queue_type() == PackageQueueType::FIFO) ? "FIFO" : "LIFO") << '\n';
        }
    }
    if (factory.storehouse_cbegin() != factory.storehouse_cend()){
        os << "; == STOREHOUSE ==" << '\n' << '\n';
        for (auto i = factory.storehouse_cbegin(); i != factory.storehouse_cend(); i++){
            os << "STOREHOUSE id =" << std::to_string(i->get_id());
        }
    }
//    if (factory.link_begin() != factory.ramp_end()){
//
//    }
}

//1b: Bartoszewski (406690), Gajek (400365), Gąsior (407326), Kowalczyk (406185)