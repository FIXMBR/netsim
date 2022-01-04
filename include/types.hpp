//1b: Bartoszewski (406690), Gajek (400365), Gąsior (407326), Kowalczyk (406185)
#ifndef NETSIM_TYPES_HPP
#define NETSIM_TYPES_HPP

#include <functional>
// #include <time.h>

using ElementID = unsigned int; // id jest tylko liczbą całkowitą dodatnią
// tutaj trzeba będzie dodawać typy, któych będziemy używać w programie

using size_type = unsigned int;

using ProbabilityGenerator = std::function<double()>;

using TimeOffset = long unsigned int;
using Time = long unsigned int;

#endif // NETSIM_TYPES_HPP

//1b: Bartoszewski (406690), Gajek (400365), Gąsior (407326), Kowalczyk (406185)