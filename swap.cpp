#include <stdio.h>
#include <string.h>

#define swap(a,b) {char tmp[10]; memcpy(tmp,&a,sizeof(a)); memcpy(&a,&b,sizeof(b)); memcpy(&b,tmp,sizeof(b));}

int main() {
    double a=2, b=3;
    swap(a,b);
    printf("%lf %lf \n", a, b);

    return 0;
}