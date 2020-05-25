#include <iostream>


class Base {
public:
    void Method1()  {  std::cout << "Base::Method1" << std::endl;  }
    virtual void Method2()  {  std::cout << "Base::Method2" << std::endl;  }
};

class Derived : public Base {
public:
    void Method1()  {  std::cout << "Derived::Method1" << std::endl;  }
    void Method2()  {  std::cout << "Derived::Method2" << std::endl;  }
};


int main() {
    Base* obj = new Derived();
    //  Note - constructed as Derived, but pointer stored as Base*

    obj->Method1();  //  Prints "Base::Method1"
    obj->Method2();  //  Prints "Derived::Method2"

    // `virtual void funcFoo() const = 0;`
    // - You can't change the state of the object
    // - You can call this function via const objects
    // - You can only call another const member functions on this object

    // `virtual void funcFoo() = 0;`
    // - You can change the state of the object
    // - You can't call this function via const objects

    return 0;
}
