#include <iostream>
#include "storage_types.hpp"

int main()
{
    std::cout << "Hello, World!" << std::endl;
    // printf("jajcos");

    PackageQueue coolkolejka(PackageQueueType::FIFO);

    coolkolejka.push(Package(1));
    coolkolejka.push(Package(3));

    Package p(std::move(coolkolejka.pop()));

    std::cout << p.get_id() << std::endl;

    p = coolkolejka.pop();

    std::cout << p.get_id() << std::endl;

    PackageQueue coolkolejka2(PackageQueueType::LIFO);

    coolkolejka2.push(Package(1));
    coolkolejka2.push(Package(3));

    p = coolkolejka2.pop();

    std::cout << p.get_id() << std::endl;

    p = coolkolejka2.pop();

    std::cout << p.get_id() << std::endl;

    return 0;
}
