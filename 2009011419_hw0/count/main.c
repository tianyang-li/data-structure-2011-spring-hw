#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

#define MAX_LEN 5000

void print_letter_count(int *count) {
    int i = 0;
    while (i != 26) {
        if (count[i]) {
            printf("%c: %d\n", (char) ('A' + i), count[i]);
        }
        ++i;
    }
}

void count_letter(char *buffer, int *count) {
    int i = 0;
    while (buffer[i] != '\0') {
        if (isalpha(buffer[i])) {
            if (islower(buffer[i])) {
                ++count[(int) (buffer[i] - 'a')];
            }
            else {
                ++count[(int) (buffer[i] - 'A')];
            }
        }
        ++i;
    }
}

int main(int argc, char **argv) {
    char *buffer = (char *) malloc(MAX_LEN * sizeof(char));
    if (!buffer) {
        printf("Cannot allocate memory!");
        return 0;
    }
    
    fgets(buffer, MAX_LEN, stdin);

    int count[27];
    
    int i = 0;
    
    while (i < 26) {
        count[i] = 0;
        ++i;
    }

    count_letter(buffer, count);
    
    print_letter_count(count);
    
    free(buffer);
    return 0;
}

