#include <iostream>
#include <thread>

using namespace std;

void thread_task() {
    std::cout << "hello thread" << std::endl;
}

int main()
{
    std::thread t(thread_task);
    t.join();

    return EXIT_SUCCESS;
}