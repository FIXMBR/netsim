#include <iostream>
#include "storage_types.hpp"
#include "nodes.hpp"

int main()
{
    Worker w(1, 2, std::make_unique<PackageQueue>(PackageQueueType::FIFO));
    Time t = 1;

    w.receive_package(Package(1));
    w.do_work(t);
    ++t;

    w.do_work(t);
    ++t;

    std::cout << "Hello, World!" << std::endl;
    std::cout << w.get_sending_buffer().has_value() << std::endl;

    // // printf("jajcos");

    // PackageQueue coolkolejka(PackageQueueType::FIFO);

    // coolkolejka.push(Package(1));
    // coolkolejka.push(Package(3));

    // Package p(std::move(coolkolejka.pop()));

    // std::cout << p.get_id() << std::endl;

    // p = coolkolejka.pop();

    // std::cout << p.get_id() << std::endl;

    // PackageQueue coolkolejka2(PackageQueueType::LIFO);

    // coolkolejka2.push(Package(1));
    // coolkolejka2.push(Package(3));

    // p = coolkolejka2.pop();

    // std::cout << p.get_id() << std::endl;

    // p = coolkolejka2.pop();

    // std::cout << p.get_id() << std::endl;

    // return 0;
}
