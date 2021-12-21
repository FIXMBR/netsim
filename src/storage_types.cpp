#include "storage_types.hpp"

Package PackageQueue::pop()
{

    Package p2(stockPile_.front());
    Package p1(stockPile_.back());
    switch (packageQueueType_)
    {
    case PackageQueueType::LIFO:
        stockPile_.pop_back();
        return p1;
        break;

    case PackageQueueType::FIFO:
        // p = stockPile_.front();
        stockPile_.pop_front();
        return p2;
        break;

    default:
        throw;
        break;
    }
}