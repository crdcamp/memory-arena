#include <stdio.h>

#include "arena.h"

int main(void) {
    int ex1 = 4;
    int ex2 = 5;

    printf("Is %i a power of two? %d\n", ex1, is_power_of_two(ex1));
    printf("Is %i a power of two? %d\n", ex2, is_power_of_two(ex2));
    return 0;
}

//
bool is_power_of_two(uintptr_t x) {
    return (x & (x-1)) == 0;
}
