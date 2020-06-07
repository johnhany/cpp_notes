#ifndef __MYLOCK_H_
#define __MYLOCK_H_
#include <iostream>
#include <atomic>
#include <thread>

class MyLock
{
private:
    std::atomic_flag m_flag;
public:
    MyLock();
    void lock();
    void unlock();
};

MyLock::MyLock()
{
    m_flag.clear(); //if not do this，m_flag will be unspecified
}

void MyLock::lock()
{
    while(m_flag.test_and_set())
        ;
}

void MyLock::unlock()
{
    m_flag.clear();
}
#endif