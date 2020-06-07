#include <iostream>
#include <thread>

using namespace std;

void thread_task() {
    std::cout << "hello thread" << std::endl;
}

int main()
{
    std::thread t(thread_task);
    std::cout << "before joining,joinable=" << std::boolalpha << t.joinable() << std::endl;
    t.join();
    std::cout << "after joining, joinable=" << std::boolalpha << t.joinable() << '\n';

    return EXIT_SUCCESS;
}