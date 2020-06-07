#include <iostream>
#include <thread>
#include <atomic>

using namespace std;

//long sum = 0L;
std::atomic_long sum = {0L};

void fun()
{
    for(int i=1;i<100000;++i)
        sum += i;
}

int main()
{
    std::cout << "Before joining,sum = " << sum << std::endl;
    std::thread t1(fun);
    std::thread t2(fun);
    t1.join();
    t2.join();
    std::cout << "After joining,sum = " << sum << std::endl;

    return EXIT_SUCCESS;
}