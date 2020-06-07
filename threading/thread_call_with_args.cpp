#include <iostream>
#include <thread>

using namespace std;


int main()
{
    int n1 = 500;
    int n2 = 600;
    std::thread t([&](int addNum){
        n1 += addNum;
        n2 += addNum;
    },500);
    t.join();
    std::cout << n1 << ' ' << n2 << std::endl;

    return EXIT_SUCCESS;
}