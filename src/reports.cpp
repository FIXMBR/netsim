#include "reports.hpp"

void generate_structure_report(const Factory &f, std::ostream &os)
{

    os << std::endl
       << "== LOADING RAMPS ==" << std::endl
       << std::endl;

    for (auto it = f.ramp_cbegin(); it != f.ramp_cend(); ++it)
    {
        os << "LOADING RAMP #" << (*it).get_id() << std::endl;
        os << "  Delivery interval: " << (*it).get_delivery_interval() << std::endl;
        os << "  Receivers:" << std::endl;

        std::vector<ElementID> receivers_v;
        for (auto itw = (*it).receiver_preferences_.cbegin(); itw != (*it).receiver_preferences_.cend(); ++itw)
        {
            receivers_v.push_back((*(*itw).first).get_id());
        }
        std::sort(receivers_v.begin(), receivers_v.end());
        for (auto itw = receivers_v.cbegin(); itw != receivers_v.cend(); ++itw)
        {
            os << "    worker #" << *itw << std::endl;
        }
        os << std::endl;
    }

    os << std::endl
       << "== WORKERS ==" << std::endl
       << std::endl;

    for (auto it = f.worker_cbegin(); it != f.worker_cend(); ++it)
    {
        os << "WORKER #" << (*it).get_id() << std::endl;
        os << "  Processing time: " << (*it).get_processing_duration() << std::endl;
        os << "  Queue type: " << (((*it).get_queue()->get_queue_type() == PackageQueueType::FIFO) ? "FIFO" : "LIFO") << std::endl;
        os << "  Receivers:" << std::endl;
        std::vector<ElementID> workers_v;
        std::vector<ElementID> storehouses_v;
        for (auto itw = (*it).receiver_preferences_.cbegin(); itw != (*it).receiver_preferences_.cend(); ++itw)
        {
            (((*(*itw).first).get_receiver_type() == ReceiverType::STOREHOUSE) ? storehouses_v : workers_v).push_back((*(*itw).first).get_id());
        }
        std::sort(workers_v.begin(), workers_v.end());
        std::sort(storehouses_v.begin(), storehouses_v.end());
        for (auto itw = storehouses_v.cbegin(); itw != storehouses_v.cend(); ++itw)
        {
            os << "    storehouse #" << *itw << std::endl;
        }
        for (auto itw = workers_v.cbegin(); itw != workers_v.cend(); ++itw)
        {
            os << "    worker #" << *itw << std::endl;
        }
        os << std::endl;
    }
    os << std::endl
       << "== STOREHOUSES ==" << std::endl
       << std::endl;

    for (auto it = f.storehouse_cbegin(); it != f.storehouse_end(); ++it)
    {
        os << "STOREHOUSE #" << (*it).get_id() << std::endl;
        os << std::endl;
    }
}

void generate_simulation_turn_report(const Factory &f, std::ostream &os, Time t)
{

    // Sprawdź, czy kontener jest pusty.
    // bool is_empty = (f.ramp_cbegin() == f.ramp_cend());

    // if(is_empty){

    // }

    os << "=== [ Turn: " << t << " ] ===" << std::endl;

    os << std::endl
       << "== WORKERS ==" << std::endl
       << std::endl;

    std::vector<const Worker *> workers_v;

    for (auto it = f.worker_cbegin(); it != f.worker_cend(); ++it)
    {
        workers_v.push_back(&(*it));
    }

    std::sort(workers_v.begin(), workers_v.end(), [](auto a, auto b)
              { return a->get_id() < b->get_id(); });

    for (auto it = workers_v.cbegin(); it != workers_v.cend(); ++it)
    {
        os << "WORKER #" << (*it)->get_id() << std::endl;
        os << "  PBuffer: ";
        if ((*it)->get_processing_buffer().has_value())
        {
            os << "#" << (*it)->get_processing_buffer()->get_id() << " (pt = " << t - (*it)->get_package_processing_start_time() + 1 << ")" << std::endl;
        }
        else
        {
            os << "(empty)" << std::endl;
        }

        os << "  Queue:";
        if ((*it)->get_queue()->cbegin() == (*it)->get_queue()->cend())
        {
            os << " (empty)";
        }
        else
        {
            for (auto itw = (*it)->get_queue()->cbegin(); itw != (*it)->get_queue()->cend(); ++itw)
            {
                bool is_last = (itw == std::prev((*it)->get_queue()->cend()));
                os << " #" << itw->get_id() << ((is_last ? "" : ","));
            }
        }
        os << std::endl
           << "  SBuffer: " << ((*it)->get_sending_buffer().has_value() ? "#" + std::to_string((*it)->get_sending_buffer()->get_id()) : "(empty)") << std::endl;
        os << std::endl;
    }
    os << std::endl
       << "== STOREHOUSES ==" << std::endl
       << std::endl;

    std::vector<const Storehouse *> storehouses_v;

    for (auto it = f.storehouse_cbegin(); it != f.storehouse_cend(); ++it)
    {
        storehouses_v.push_back(&(*it));
    }

    std::sort(storehouses_v.begin(), storehouses_v.end(), [](auto a, auto b)
              { return a->get_id() < b->get_id(); });

    for (auto it = storehouses_v.cbegin(); it != storehouses_v.cend(); ++it)
    {
        os << "STOREHOUSE #" << (*it)->get_id() << std::endl;
        os << "  Stock:";
        if ((*it)->cbegin() == (*it)->cend())
        {
            os << " (empty)";
        }
        else
        {
            for (auto itw = (*it)->cbegin(); itw != (*it)->cend(); ++itw)
            {
                bool is_last = (itw == std::prev((*it)->cend()));
                os << " #" << itw->get_id() << ((is_last ? "" : ","));
            }
        }
        os << std::endl;
    }
    os << std::endl;
}