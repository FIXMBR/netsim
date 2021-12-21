//1b: Bartoszewski (406690), Gajek (400365), Gąsior (407326), Kowalczyk (406185)
#ifndef NETSIM_STORAGE_TYPES_HPP
#define NETSIM_STORAGE_TYPES_HPP

#include <list>
#include "types.hpp"
#include "package.hpp"

enum class PackageQueueType
{
    FIFO,
    LIFO
};

class IPackageStockPile
{
public:
    using const_iterator = std::list<Package>;
    virtual void push(Package &&package) = 0;
    virtual bool empty() const = 0;
    virtual size_type size() const = 0;
    virtual ~IPackageStockPile(){};
};

class IPackageQueue : public IPackageStockPile
{
public:
    virtual PackageQueueType get_queue_type() const = 0;
    virtual Package pop() = 0;
    virtual ~IPackageQueue() override{};
};

class PackageQueue : public IPackageQueue
{
private:
    const_iterator stockPile_;
    PackageQueueType packageQueueType_;

public:
    PackageQueue(PackageQueueType newPackageQueueType) : packageQueueType_(newPackageQueueType){};

    ~PackageQueue() override{};

    void push(Package &&package) { stockPile_.push_back(package); };
    bool empty() const { return stockPile_.empty(); };
    size_type size() const { return size_type(stockPile_.size()); };

    PackageQueueType get_queue_type() const { return packageQueueType_; };

    Package pop() override;
};

#endif // NETSIM_TYPES_HPP
//1b: Bartoszewski (406690), Gajek (400365), Gąsior (407326), Kowalczyk (406185)