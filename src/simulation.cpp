//1b: Bartoszewski (406690), Gajek (400365), Gąsior (407326), Kowalczyk (406185)

#include "simulation.hpp"
void simulate(Factory& f, TimeOffset d, std::function<void (Factory&, Time)> rf){
    for (Time i = 1; i<=d;i++ ){
    f.do_deliveries(i);
    f.do_package_passing();
    f.do_work(i);
    rf(f,i);
    }
}
//1b: Bartoszewski (406690), Gajek (400365), Gąsior (407326), Kowalczyk (406185)