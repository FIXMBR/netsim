#include "reports.hpp"

void generate_structure_report(const Factory &f, std::ostream &os)
{
    // Sprawdź, czy kontener jest pusty.
    // bool is_empty = (f.ramp_cbegin() == f.ramp_cend());

    // if(is_empty){

    // }

    os << std::endl
       << "== LOADING RAMPS ==" << std::endl
       << std::endl;

    for (auto it = f.ramp_cbegin(); it != f.ramp_cend(); ++it)
    {
        // Sprawdź, czy iterator wskazuje na ostatni element w kontenerze.
        // bool is_last = (it == std::prev(f.ramp_cend()));

        os << "LOADING RAMP #" << (*it).get_id() << std::endl;
        os << "  Delivery interval: " << (*it).get_delivery_interval() << std::endl;
        os << "  Receivers:" << std::endl;
        for (auto itw = (*it).receiver_preferences_.cbegin(); itw != (*it).receiver_preferences_.cend(); ++itw)
        {
            os << "    worker #" << (*(*itw).first).get_id() << std::endl;
        }
        os << std::endl;
    }

    os << std::endl
       << "== WORKERS ==" << std::endl
       << std::endl;

    for (auto it = f.worker_cbegin(); it != f.worker_cend(); ++it)
    {
        // Sprawdź, czy iterator wskazuje na ostatni element w kontenerze.
        // bool is_last = (it == std::prev(f.ramp_cend()));

        os << "WORKER #" << (*it).get_id() << std::endl;
        os << "  Processing time: " << (*it).get_processing_duration() << std::endl;
        os << "  Queue type: " << (*it).cbegin().get_queue_type() << std::endl;
        os << "  Receivers:" << std::endl;
        for (auto itw = (*it).receiver_preferences_.cbegin(); itw != (*it).receiver_preferences_.cend(); ++itw)
        {
            os << "    worker #" << (*(*itw).first).get_id() << std::endl;
        }
        os << std::endl;
    }
}

void generate_simulation_turn_report(const Factory &f, std::ostream &os, Time t)
{
}