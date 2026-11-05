#include <stdint.h>
#include <stdio.h>

#include "arena.h"

int main(void) {

    return 0;
}

// Memory alignment must be a power of 2
bool is_power_of_two(uintptr_t x) {
    return (x & (x-1)) == 0;
}

uintptr_t align_forward(uintptr_t ptr, size_t align) {
    uintptr_t p, a, modulo;

    assert(is_power_of_two(align));

    p = ptr; // So we don't accidentally edit the pointer passed to the function
    // Not really sure why we use this though. Why not just cast the original variable?
    // Might be for the same reason of avoiding editing the original variable
    a = (uintptr_t)align;

    // Same as `%` but is faster since `a` is a power of two
    modulo = p & (a-1);

    // If the pointer is not aligned, take the alignment minus
    // the modulo and add it to the pointer
    // This way, you're able to make up the difference in bytes
    // to reach the next aligned place for your pointer
    if (modulo != 0) {
        p += a-modulo;
    }

    // Return the newly aligned pointer (without editing the passed pointer)
    return p;
}

void *arena_alloc_align(Arena *arena, size_t size, size_t align) {
    // Align `curr_offset` forward to the specified alignment
    // We do this by taking the buffer (`arena->buffer` - where the arena's memory begins)
    // and adding the arena's current offset (`arena->current_offset`) to get where the available
    // memory begins. We set `curr_ptr` to this location in memory to continue
    uintptr_t curr_ptr = (uintptr_t)arena->buffer + (uintptr_t)arena->current_offset;

    // Checks if the alignment is a power of two and moves `curr_ptr` to the next
    // point in memory that's aligned

    // `align_forward` takes the `curr_ptr` and moves it to an aligned
    // location. We then use `offset` from here on out to handle the rest
    // of the function
    uintptr_t offset = align_forward(curr_ptr, align);
    // Change to relative offset
    // I don't fully understand how this makes sense. Doesn't the
    // above line effectively do this for us?
    offset -= (uintptr_t)arena->buffer;
}
