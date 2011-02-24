#include <stdlib.h>
#include <stdio.h>

int gcd(int a, int b) {
    if (a == b) {
        return a;
    }
    if (a > b) {
        return gcd(a - b, b);
    }
    else {
        return gcd(b - a, a);
    }
}

int main(int argc, char **argv) {
    int a, b;
    scanf("%d %d", &a, &b);
    printf("%d\n", gcd(a, b));
    return 0;
}


