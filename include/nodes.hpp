//1b: Bartoszewski (406690), Gajek (400365), Gąsior (407326), Kowalczyk (406185)
#ifndef NODES_HPP
#define NODES_HPP

#include <optional>
#include <map>
#include <memory>
#include "package.hpp"
#include "types.hpp"
#include "storage_types.hpp"
// #include "helpers.hpp"

class IPackageReceiver //tutaj trzeba dodać get_receiver_type() dopiero po wysłaniu węzłów sieci!!!
{
public:
    [[nodiscard]] virtual IPackageStockPile::const_iterator cbegin() const = 0; // zwraca stały iterator na pierwszy element kontenera
    [[nodiscard]] virtual IPackageStockPile::const_iterator cend() const = 0 ; // zwraca stały iterator na ostatni element kontenera
    [[nodiscard]] virtual IPackageStockPile::const_iterator begin() const = 0; //
    [[nodiscard]] virtual IPackageStockPile::const_iterator end() const = 0 ;
    virtual void receive_package(Package &&p) = 0;
    [[nodiscard]] virtual ElementID get_id() const = 0;
};

class ReceiverPreferences
{
private:
    using preferences_t = std::map<IPackageReceiver *, double>;
    using const_iterator = preferences_t::const_iterator;
    void calculatePropability();
    preferences_t preferences_;
    ProbabilityGenerator pg_;
public:
    ReceiverPreferences(ProbabilityGenerator pg) : pg_(pg){};
    void add_receiver(IPackageReceiver *r);
    void remove_receiver(IPackageReceiver *r);
    IPackageReceiver *choose_receiver();
    const preferences_t &get_preferences() const { return preferences_; };
};

class PackageSender
{
private:
    std::optional<Package> sending_buffer_ = std::nullopt;

public:
    ReceiverPreferences receiver_preferences_;
    PackageSender(PackageSender &&);
    void send_package();

protected:
    const std::optional<Package> &get_sending_buffer() const { return sending_buffer_; };
    void push_package(Package&&);
};

class Ramp : PackageSender
{
private:
    TimeOffset timeOffset_; //to może być źle
    ElementID id_;          //to jeszcze bardziej

public:
    Ramp(ElementID id, TimeOffset di);
    void deliver_goods(Time t);
    TimeOffset get_delivery_interval() const { return timeOffset_; };
    ElementID get_id() const { return id_; };
};

class Worker : IPackageReceiver, PackageSender, IPackageQueue
{
private:
    TimeOffset time_offset_;
    std::unique_ptr<IPackageQueue> q_;
    ElementID id_;
    std::optional<Package> buffer_queue_ = std::nullopt;
public:
    static Time time_;
    Worker(ElementID id, TimeOffset pd, std::unique_ptr<IPackageQueue> q) {}; //tutaj trzeba coś zainizjalizować (ciekawe co)
    void do_work(Time time){};
    TimeOffset get_processing_duration(void) const {return time_offset_; };
    Time get_package_processing_start_time(void) const {return time_;};
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
private:

public:
    Storehouse(ElementID id, std::unique_ptr<IPackageStockPile> d);
};


#endif //NODES_HPP

//1b: Bartoszewski (406690), Gajek (400365), Gąsior (407326), Kowalczyk (406185)
