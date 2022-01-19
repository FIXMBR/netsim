//1b: Bartoszewski (406690), Gajek (400365), Gąsior (407326), Kowalczyk (406185)
#ifndef NETSIM_SIMULAION_HPP
#define NETSIM_SIMULAION_HPP

#include "factory.hpp"


void simulate(Factory& f, TimeOffset d, std::function<void (Factory&, Time)> rf);

#endif //NETSIM_SIMULAION_HPP
//1b: Bartoszewski (406690), Gajek (400365), Gąsior (407326), Kowalczyk (406185)