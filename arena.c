#include <stdio.h>

#include "arena.h"

int main(void) {

    return 0;
}

// Memory alignment must be a power of 2
bool is_power_of_two(uintptr_t x) {
    return (x & (x-1)) == 0;
}

//
uintptr_t align_forward(uintptr_t ptr, size_t align) {
    uintptr_t p, a, modulo;

    assert(is_power_of_two(align));

    p = ptr; // So we don't accidentally edit the pointer passed to the function
    a = (uintptr_t)align; // Not really sure why we use this though. Why not just cast the original variable?

    // Same as `%` but is faster since `a` is a power of two
    modulo = p & (a-1);

    // If the pointer is not aligned, take the alignment minus
    // the modulo and add it to the pointer
    // This way, you're able to make up the difference in bytes
    // to reach the next aligned place for your pointer
    if (modulo != 0) {
        p += a - modulo;
    }

    // Return the newly aligned pointer (without editing the passed pointer)
    return p;
}

void *arena_alloc_align(Arena arena, size_t size, size_t align) {
    printf("Not implemented\n");
    return 0;
}
