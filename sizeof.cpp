#include <iostream>

using namespace std;

class A {
    private:
    bool a;
    int b;
    bool c;
};

class B {
    private:
    int a;
    bool b;
    bool c;
};

int main()
{
    cout << sizeof(A) << endl;
    cout << sizeof(B) << endl;

    return EXIT_SUCCESS;
}