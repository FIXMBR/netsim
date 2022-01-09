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
    void add(Node &&node) { collection_.push_back(node); };
    void remove_by_id(ElementID id)
    {
        collection_.remove_if([id](Node n) //TODO vibecheck czy to działa
                              { return n.get_id() == id; });
    };
    NodeCollection<Node>::iterator find_by_id(ElementID id)
    {
        return std::find_if(collection_.begin(), collection_.end(), [id](Node n)
                            { return n == id; });
    };
    NodeCollection<Node>::const_iterator find_by_id(ElementID id) const
    {
        return std::find_if(collection_.cbegin(), collection_.cend(), [id](Node n)
                            { return n == id; });
    };
    const_iterator begin() const { return collection_.begin(); };
    const_iterator cbegin() const { return collection_.cbegin(); };
    const_iterator end() const { return collection_.end(); };
    const_iterator cend() const { return collection_.cend(); };

private:
    container_t collection_;
};

#endif //NETSIM_FACTORY_HPP

//1b: Bartoszewski (406690), Gajek (400365), Gąsior (407326), Kowalczyk (406185)