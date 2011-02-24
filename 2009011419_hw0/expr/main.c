#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>

#define MAX_LEN 100

int main(int argc, char **argv) {
    char buffer[MAX_LEN];
    fgets(buffer, MAX_LEN, stdin);
    
    char num1[MAX_LEN], num2[MAX_LEN], op;
    
    int i = 0;
    int second = 0;  /* true if in the second number */
    int num_pos = 0;
    while (buffer[i] != '\0' && i != MAX_LEN) {
        if (!second) {
            if ('0' <= buffer[i] && buffer[i] <= '9') {
                num1[num_pos] = buffer[i];
                ++num_pos;
            }
            else {
                if (buffer[i] == '*' || buffer[i] == '-' || buffer[i] == '+') {
                    second = 1;
                    num1[num_pos] = '\0';
                    num_pos = 0;
                    op = buffer[i];
                }
            }
        }
        else {
            if ('0' <= buffer[i] && buffer[i] <= '9') {
                num2[num_pos] = buffer[i];
                ++num_pos;
            }
        }
        ++i;
    }
    num2[num_pos] = '\0';
    
    switch (op) {
        case '*':
            printf("%lld\n", ((int64_t) atoi(num1)) * ((int64_t) atoi(num2)));
            break;
        case '-':
            printf("%lld\n", ((int64_t) atoi(num1)) - ((int64_t) atoi(num2)));
            break;
        case '+':
            printf("%lld\n", ((int64_t) atoi(num1)) + ((int64_t) atoi(num2)));
            break;
    }
    
    return 0;
}

