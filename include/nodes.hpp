// 1b: Bartoszewski (406690), Gajek (400365), Gąsior (407326), Kowalczyk (406185)
#ifndef NODES_HPP
#define NODES_HPP

#include <optional>
#include <map>
#include <memory>
#include "package.hpp"
#include "types.hpp"
#include "storage_types.hpp"
#include "helpers.hpp"

enum class ReceiverType
{
    WORKER,
    STOREHOUSE
};

class IPackageReceiver // tutaj trzeba dodać get_receiver_type() dopiero po wysłaniu węzłów sieci!!!
{
public:
    virtual IPackageStockpile::const_iterator cbegin() const = 0; // zwraca stały iterator na pierwszy element kontenera
    virtual IPackageStockpile::const_iterator cend() const = 0;   // zwraca stały iterator na ostatni element kontenera
    virtual IPackageStockpile::const_iterator begin() const = 0;  //
    virtual IPackageStockpile::const_iterator end() const = 0;
    virtual void receive_package(Package &&p) = 0;
    virtual ElementID get_id() const = 0;
    virtual ReceiverType get_receiver_type() const = 0;
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
    // ReceiverPreferences() = default;
    ReceiverPreferences(ProbabilityGenerator pg = probability_generator) : pg_(pg){};
    void add_receiver(IPackageReceiver *r);
    void remove_receiver(IPackageReceiver *r);
    IPackageReceiver *choose_receiver();
    const preferences_t &get_preferences() const { return preferences_; };

    const_iterator begin() const { return preferences_.begin(); };
    const_iterator cbegin() const { return preferences_.cbegin(); };
    const_iterator end() const { return preferences_.end(); };
    const_iterator cend() const { return preferences_.cend(); };
};

class PackageSender
{
private:
    std::optional<Package> sending_buffer_ = std::nullopt;

public:
    ReceiverPreferences receiver_preferences_;

    PackageSender() { receiver_preferences_ = ReceiverPreferences(); };

    PackageSender(PackageSender &&) = default;

    void send_package();

    virtual ~PackageSender() = default;

    const std::optional<Package> &get_sending_buffer() const { return sending_buffer_; };

protected:
    void push_package(Package &&p) { sending_buffer_ = p; };
};

class Ramp : public PackageSender
{
private:
    TimeOffset di_; // to może być źle
    ElementID id_;  // to jeszcze bardziej

public:
    Ramp(ElementID id, TimeOffset di) : di_(di), id_(id){};
    void deliver_goods(Time t);
    TimeOffset get_delivery_interval() const { return di_; };
    ElementID get_id() const { return id_; };
};

class Worker : public IPackageReceiver, public PackageSender
{
private:
    std::unique_ptr<IPackageQueue> q_;
    ElementID id_;
    TimeOffset pd_; // jak długo się coś robi
    std::optional<Package> buffer_queue = std::nullopt;
    Time work_start_time = 0;

public:
    static Time time_;
    Worker(ElementID id, TimeOffset pd, std::unique_ptr<IPackageQueue> q) : q_(std::move(q)), id_(id), pd_(pd), buffer_queue(std::nullopt){};
    void do_work(Time time);
    TimeOffset get_processing_duration(void) const { return pd_; };
    Time get_package_processing_start_time(void) const { return time_; };
    ElementID get_id() const override { return id_; };
    void receive_package(Package &&p) override { q_->push(std::move(p)); };
    IPackageStockpile::const_iterator begin() const override { return q_->begin(); };
    IPackageStockpile::const_iterator cbegin() const override { return q_->cbegin(); };
    IPackageStockpile::const_iterator end() const override { return q_->end(); };
    IPackageStockpile::const_iterator cend() const override { return q_->cend(); };
    ReceiverType get_receiver_type() const override { return ReceiverType::WORKER; };
    std::unique_ptr<IPackageQueue> get_processing_buffer() const { return q_; };
};

// Odbiorca półproduktów
// Interfejs IPackageReceiver powinien posiadać metodę do “odbioru” półproduktu, metody delegujące2) pozwalające na uzyskanie dostępu
//  “tylko do odczytu” do kontenera przechowującego półprodukty (tj. metody [c]begin(), [c]end()),
//  oraz metody identyfikujące danego odbiorcę (tj. jego typ oraz ID).
// Definiując powyższe metody delegujące skorzystaj z typu IPackageStockpile::const_iterator (zob. tu).

// class IPackageStockpile
//{
// public:
//     using const_iterator = std::list<Package>;
//     virtual void push(Package &&package) = 0;
//     virtual bool empty() const = 0;
//     virtual size_type size() const = 0;
//     virtual ~IPackageStockpile(){};
// };

class Storehouse : public IPackageReceiver
{
private:
    // std::unique_ptr<IPackageQueue> q_;
    ElementID id_;
    std::unique_ptr<IPackageStockpile> d_;

public:
    Storehouse(ElementID id, std::unique_ptr<IPackageStockpile> d = std::make_unique<PackageQueue>(PackageQueue(PackageQueueType::LIFO))) : id_(id), d_(std::move(d)){};
    ElementID get_id() const override { return id_; };
    void receive_package(Package &&p) override { d_->push(std::move(p)); };
    IPackageStockpile::const_iterator begin() const override { return d_->begin(); };
    IPackageStockpile::const_iterator cbegin() const override { return d_->cbegin(); };
    IPackageStockpile::const_iterator end() const override { return d_->end(); };
    IPackageStockpile::const_iterator cend() const override { return d_->cend(); };
    ReceiverType get_receiver_type() const override { return ReceiverType::STOREHOUSE; };
};

#endif // NODES_HPP

// 1b: Bartoszewski (406690), Gajek (400365), Gąsior (407326), Kowalczyk (406185)