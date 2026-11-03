#include <stdio.h>

#include "arena.h"

int main(void) {
    uintptr_t p = 10;
    size_t a = 7;
    uintptr_t result = align_forward(p, a);

    return 0;
}

// Memory alignment must be a power of 2
bool is_power_of_two(uintptr_t x) {
    return (x & (x-1)) == 0;
}

// Using power of 2 check, align
uintptr_t align_forward(uintptr_t ptr, size_t align) {
    uintptr_t p, a, modulo;

    assert(is_power_of_two(align));

    // If the pointer is not aligned (must be a powerw   power of two)
    p = ptr;
    a = (uintptr_t)align;
    modulo = p & (a-1);
    if (modulo != 0) {
        p += a - modulo;
    }

    return p;
}
