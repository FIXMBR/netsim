//1b: Bartoszewski (406690), Gajek (400365), Gąsior (407326), Kowalczyk (406185)
#include "storage_types.hpp"

Package PackageQueue::pop()
{
    Package p;
    switch (packageQueueType_)
    {
    case PackageQueueType::LIFO:
        p = stockPile_.back();
        stockPile_.pop_back();
        return p;
        break;

    case PackageQueueType::FIFO:
        p = stockPile_.front();
        stockPile_.pop_front();
        return p;
        break;

    default:
        return p;
        break;
    }
}
//1b: Bartoszewski (406690), Gajek (400365), Gąsior (407326), Kowalczyk (406185)