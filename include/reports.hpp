//1b: Bartoszewski (406690), Gajek (400365), Gąsior (407326), Kowalczyk (406185)
#ifndef NETSIM_REPORTS_HPP
#define NETSIM_REPORTS_HPP

#include "factory.hpp"

void generate_structure_report(const Factory &f, std::ostream &os);
void generate_simulation_turn_report(const Factory &f, std::ostream &os, Time t);

#endif //NETSIM_REPORTS_HPP

//1b: Bartoszewski (406690), Gajek (400365), Gąsior (407326), Kowalczyk (406185)