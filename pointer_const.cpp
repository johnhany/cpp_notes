#include <stdio.h>

int main() {
    char *pBuffer = new char[10];
    for (int i=0; i<10; i++)
        printf("%d ", *(pBuffer+i));
    printf("\n");
    for (int i=0; i<10; i++)
        printf("%d ", *pBuffer+i);
    printf("\n");
    char *pBuffer2 = new char[10]();
    for (int i=0; i<10; i++)
        printf("%d ", *(pBuffer2+i));
    printf("\n");

    int const value = 5; // value is const
    //int *ptr = &value; // compile error: cannot convert const int* to int*
    //*ptr = 6; // change value to 6

    int const *ptr = &value;
    //*ptr = 6; // not allowed, we can't change a const value

    int value2 = 5;
    int const *ptr2 = &value2;
    value2 = 6; // the value is non-const when accessed through a non-const identifier
    //*ptr2 = 6; // ptr treats its value as const, so changing the value through ptr is not legal

    ptr = &value2; // okay, ptr now points at some other const int

    int *const ptr3 = &value2;
    //ptr3 = &value2; // not okay, once initialized, a const pointer can not be changed.

    *ptr3 = 6; // allowed, since ptr points to a non-const int

    const int *const ptr4 = &value2;

    return 0;
}