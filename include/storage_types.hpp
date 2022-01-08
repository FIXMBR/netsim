// 1b: Bartoszewski (406690), Gajek (400365), Gąsior (407326), Kowalczyk (406185)
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

class IPackageStockpile
{
public:
    virtual ~IPackageStockpile() = default;
    using const_iterator = std::list<Package>::const_iterator;
    virtual void push(Package &&package) = 0;
    virtual bool empty() const = 0;
    virtual size_type size() const = 0;
    virtual const_iterator begin() const = 0;
    virtual const_iterator cbegin() const = 0;
    virtual const_iterator end() const = 0;
    virtual const_iterator cend() const = 0;
};

class IPackageQueue : public IPackageStockpile
{
public:
    virtual PackageQueueType get_queue_type() const = 0;
    virtual Package pop() = 0;
    virtual ~IPackageQueue() override{};
};

class PackageQueue : public IPackageQueue
{
private:
    std::list<Package> stockPile_;
    PackageQueueType packageQueueType_;

public:
    PackageQueue(PackageQueueType newPackageQueueType) : packageQueueType_(newPackageQueueType){};

    ~PackageQueue() override{};

    void push(Package &&package) override { stockPile_.push_back(package); };
    bool empty() const override { return stockPile_.empty(); };
    size_type size() const override { return size_type(stockPile_.size()); };

    PackageQueueType get_queue_type() const override { return packageQueueType_; };

    const_iterator begin() const override { return stockPile_.begin(); };
    const_iterator cbegin() const override { return stockPile_.cbegin(); };
    const_iterator end() const override { return stockPile_.end(); };
    const_iterator cend() const override { return stockPile_.cend(); };
    Package pop() override;
};

#endif // NETSIM_TYPES_HPP

// 1b: Bartoszewski (406690), Gajek (400365), Gąsior (407326), Kowalczyk (406185)