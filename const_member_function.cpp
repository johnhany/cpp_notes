#include <iostream>

using namespace std;


class MyClass {
private:
    int counter;
public:
    void Foo() {
        counter++;
        std::cout << "Foo" << std::endl;
    }

    void Foo() const {
        //counter++;
        std::cout << "Foo const" << std::endl;
    }

    int GetInvocations() const {
        return counter;
    }

};

class MyClass2 {
private:
    mutable int counter;
public:

    MyClass2() : counter(0) {}

    void Foo() {
        counter++;
        std::cout << "Foo" << std::endl;
    }

    void Foo() const {
        counter++;
        std::cout << "Foo const" << std::endl;
    }

    int GetInvocations() const {
        return counter;
    }
};

int main() {
    MyClass cc;
    const MyClass& ccc = cc;
    cc.Foo();
    ccc.Foo();
    std::cout << "Foo has been invoked " << ccc.GetInvocations() << " times" << endl;

    MyClass2 dd;
    const MyClass2& ddd = dd;
    dd.Foo();
    ddd.Foo();
    std::cout << "Foo has been invoked " << ddd.GetInvocations() << " times" << endl;

    return 0;
}