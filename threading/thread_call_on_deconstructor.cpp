#include <iostream>
#include <thread>

using namespace std;


class thread_guard
{
    thread &t;
public :
    explicit thread_guard(thread& _t) :
        t(_t){}

    ~thread_guard()
    {
        if (t.joinable())
            t.join();
    }

    thread_guard(const thread_guard&) = delete;
    thread_guard& operator=(const thread_guard&) = delete;
};

int main()
{
    thread t([]{
        cout << "Hello thread" <<endl ;
    });

    thread_guard g(t);

    return EXIT_SUCCESS;
}