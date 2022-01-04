//1b: Bartoszewski (406690), Gajek (400365), Gąsior (407326), Kowalczyk (406185)
#ifndef NODES_HPP
#define NODES_HPP

#include <optional>
#include <map>
#include "package.hpp"
#include "types.hpp"
#include "storage_types.hpp"
// #include "helpers.hpp"

class IPackageReceiver
{
public:
    virtual IPackageStockPile::const_iterator cbegin();

    virtual void receive_package(Package &&p) = 0;
};

class ReceiverPreferences
{
private:
    using preferences_t = std::map<IPackageReceiver *, double>;
    using const_iterator = preferences_t::const_iterator;

public:
    ReceiverPreferences(ProbabilityGenerator pg);
    void add_receiver(IPackageReceiver *r);
    void remove_receiver(IPackageReceiver *r);
    IPackageReceiver *choose_receiver();
    preferences_t &get_preferences() const;
};

class PackageSender
{
private:
public:
    ReceiverPreferences receiver_preferences_;
    PackageSender(PackageSender &&);
    void send_package();

protected:
    std::optional<Package> &get_sending_buffer() const;
};

class Ramp : PackageSender
{
public:
    Ramp(ElementID id, TimeOffset di);
    void deliver_goods(Time t);
    TimeOffset get_delivery_interval() const;
    ElementID get_id() const;
};

class Worker
{
public:
    Worker(id
           : ElemendID, pd
           : TimeOffset, q
           : std::unique_ptr<IPackageQueue>){};
    void do_work(t
                 : Time){};
    int get_processing_duration(void) { return TimeOffset; };
    int get_package_processing_start_time(void) const { return Time; };
};

//Odbiorca półproduktów
//Interfejs IPackageReceiver powinien posiadać metodę do “odbioru” półproduktu, metody delegujące2) pozwalające na uzyskanie dostępu
// “tylko do odczytu” do kontenera przechowującego półprodukty (tj. metody [c]begin(), [c]end()),
// oraz metody identyfikujące danego odbiorcę (tj. jego typ oraz ID).
//Definiując powyższe metody delegujące skorzystaj z typu IPackageStockpile::const_iterator (zob. tu).

class IPackageStockPile
{
public:
    using const_iterator = std::list<Package>;
    virtual void push(Package &&package) = 0;
    virtual bool empty() const = 0;
    virtual size_type size() const = 0;
    virtual ~IPackageStockPile(){};
};

class Storehouse
{
    Storehouse(id
               : ElementID, d
               : std::unique_ptr<IPackageStockpile>);
};

#endif //NODES_HPP

//1b: Bartoszewski (406690), Gajek (400365), Gąsior (407326), Kowalczyk (406185)