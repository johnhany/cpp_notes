#include <iostream>

using namespace std;


struct A
{
    int a;
    int b;
};

int main() {

    A obj;
    int A::* ptr_to_memb = &A::b;

    obj.*ptr_to_memb = 5;

    ptr_to_memb = &A::a;

    obj.*ptr_to_memb = 7;

    cout << obj.a << endl;
    cout << obj.b << endl;


    return 0;
}