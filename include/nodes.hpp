//1b: Bartoszewski (406690), Gajek (400365), Gąsior (407326), Kowalczyk (406185)
#ifndef NODES_HPP
#define NODES_HPP

#include <optional>
#include "package.hpp"
class ReceiverPreferences
{
public:
    ReceiverPreferences(PropabilityGenerator pg);
    void add_receiver(IPackageReceiver *r);
    void remove_receiver(IPackageReceiver *r);
    IPackageReceiver *choose_receiver();
    preferences_t &get_preferences() const;
};

class PackageSender
{
private:
public:
    ReceiverPreferences receiver_preferences_;
    PackageSender(PackageSender &&);
    void send_package();

protected:
    std::optional<Package> &get_sending_buffer() const;
};

#endif //NODES_HPP \
       //1b: Bartoszewski (406690), Gajek (400365), Gąsior (407326), Kowalczyk (406185)