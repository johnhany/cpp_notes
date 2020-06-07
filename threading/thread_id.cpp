#include <iostream>
#include <thread>

using namespace std;

void thread_task() {
    std::cout << std::this_thread::get_id() << std::endl;
}

int main()
{
    std::thread t(thread_task);
    std::cout << t.get_id() << std::endl;
    t.join();

    return EXIT_SUCCESS;
}