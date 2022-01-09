//1b: Bartoszewski (406690), Gajek (400365), Gąsior (407326), Kowalczyk (406185)
#ifndef NETSIM_FACTORY_HPP
#define NETSIM_FACTORY_HPP

#include "types.hpp"
#include "nodes.hpp"

template <class Node>
class NodeCollection
{

public:
    using container_t = typename std::list<Node>;
    using iterator = typename container_t::iterator;
    using const_iterator = typename container_t::const_iterator;
    void add(Node &&node) { collection_.push_back(std::move(node)); };
    void remove_by_id(ElementID id)
    {
        collection_.remove_if([id](Node n) //TODO vibecheck czy to działa
                              { return n.get_id() == id; });
    };
    NodeCollection<Node>::iterator find_by_id(ElementID id)
    {
        return std::find_if(collection_.begin(), collection_.end(), [id](Node n)
                            { return n.get_id() == id; });
    };
    NodeCollection<Node>::const_iterator find_by_id(ElementID id) const
    {
        return std::find_if(collection_.cbegin(), collection_.cend(), [id](Node n)
                            { return n.get_id() == id; });
    };
    const_iterator begin() const { return collection_.begin(); };
    const_iterator cbegin() const { return collection_.cbegin(); };
    const_iterator end() const { return collection_.end(); };
    const_iterator cend() const { return collection_.cend(); };
    iterator begin() { return collection_.begin(); };
    iterator end() { return collection_.end(); };

private:
    container_t collection_;
};


class Factory{
private:
    NodeCollection<Ramp> ramp_collection_;
    NodeCollection<Worker> worker_collection_;
    NodeCollection<Storehouse> storehouse_collection_;
    template <class Node> void remove_receiver(NodeCollection<Node>& collection, ElementID id){
        for (auto& node : collection) {
            node.receiver_preferences_.remove_receiver(receiver);
        }
    }

public:
    NodeCollection<Ramp>::const_iterator ramp_cbegin() const { return ramp_collection_.begin(); }; // zwraca stały iterator na pierwszy element kontenera
    NodeCollection<Ramp>::const_iterator ramp_cend() const { return ramp_collection_.cend(); };   // zwraca stały iterator na ostatni element kontenera
    NodeCollection<Ramp>::const_iterator ramp_begin() const { return ramp_collection_.begin(); };  //
    NodeCollection<Ramp>::const_iterator ramp_end() const { return ramp_collection_.end(); };

    void add_ramp(Ramp&& r){ramp_collection_.add(std::move(r));};
    void remove_ramp(ElementID id){remove_receiver(ramp_collection_,id);};
    NodeCollection<Ramp>::iterator find_ramp_by_id(ElementID id) {return ramp_collection_.find_by_id(id); };
    NodeCollection<Ramp>::const_iterator find_ramp_by_id(ElementID id)const{return ramp_collection_.find_by_id(id); };

    NodeCollection<Storehouse>::const_iterator storehouse_cbegin() const { return storehouse_collection_.cbegin(); }; // zwraca stały iterator na pierwszy element kontenera
    NodeCollection<Storehouse>::const_iterator storehouse_cend() const { return storehouse_collection_.cend(); };   // zwraca stały iterator na ostatni element kontenera
    NodeCollection<Storehouse>::const_iterator storehouse_begin() const { return storehouse_collection_.begin(); };  //
    NodeCollection<Storehouse>::const_iterator storehouse_end() const { return storehouse_collection_.end(); };

    void add_storehouse(Storehouse&& s){storehouse_collection_.add(std::move(s));};
    void remove_storehouse(ElementID id){remove_receiver(storehouse_collection_,id);};
    NodeCollection<Storehouse>::iterator find_storehouse_by_id(ElementID id) {return storehouse_collection_.find_by_id(id); };
    NodeCollection<Storehouse>::const_iterator find_storehouse_by_id(ElementID id)const{return storehouse_collection_.find_by_id(id); };

    bool is_consistent(void) const ;//FIXME
    void do_deliveries(Time time);
    void do_package_passing(void);
    void do_work(Time time);
};

#endif //NETSIM_FACTORY_HPP

//1b: Bartoszewski (406690), Gajek (400365), Gąsior (407326), Kowalczyk (406185)