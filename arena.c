#include <stdint.h>
#include <string.h>

#include "arena.h"

int main(void) {
    return 0;
}

// Note:"`uintptr_t` is an unsigned integer type with the property
// that any valid pointer to void can be converted to this type, then
// converted back to pointer to void, and the result will compare
// equal to the original pointer"
// Pretty not great explanation, but I think I understand

// So, it's essentially a data type that allows us to pass void
// type pointers to it without any isues, which also enables us
// to store something that's the same size of the pointer. I think
// it's a way of not enforcing types when creating memory so aggressively

// I think it might be some combination of cross compatibility and
// some other sort of practices also... I have no idea honestly
// I'm in a bit over my head right now

bool is_power_of_two(uintptr_t x) {
    // This is some crazy bitwise wizardry that I've never seen
    // before, so... yea. Pretty cool. As you can tell by the
    // function name, it returns whether the value is a power of 2
    return (x & (x-1)) == 0;
}

// To align a memory address to the specified alignment is simple
// modulo arithmetic. You are looking to find how many bytes forward
// you need to go in order to ensure the memory address is a multiple
// of the specified alignment
uintptr_t align_forward(uintptr_t ptr, size_t align) {
    uintptr_t p, a, modulo;

    // Exits function if false
    // Not sure why you'd use assert here though
    // (I thought assert was meant to be used primarily for testing?)
    // Make sure to look into this some more later
    assert(is_power_of_two(align));

    // Why do we assign p to the pointer though? Why not just directly work with the pointer?
    // Like, why would we want to avoid editing the original pointer in this case?
    // Maybe this will become clearer when we actually see the function called
    // I can see this making sense for `ptr`, but I still have no idea where `align` is supposed to come from
    p = ptr;
    a = (uintptr_t)align; // Don't get confused dumbass we're just casting types here

    // Below is the same as (p % a) but faster as `a` is a power of two
    // (basically some more bitwise wizardry that I need to study)
    // The bitwise `&` operator compares each bit at the same position
    // in the integer and the resultant bit will be set (1) only if both
    // corresponding bits are set (1), otherwise it will be unset (0)
    modulo = p & (a-1);

    // If `p` address is not aligned, push the address to the next
    // value which is aligned
    if (modulo != 0) {
        p += a - modulo;
    }
    return p;
}

// Now that we know how to align memory, that means we can create an
// an `arena_alloc` function that supports proper alignment and store
// data in an `Arena` structure
void *arena_alloc_align(Arena *arena, size_t size, size_t align) {
    // Align `curr_offset` forward to the specified alignment
    // I still have no fucking idea what the buffer is means for, or where `align` is supposed to come from
    // I'm pretty sure the "buffer" is actually supposed to be the point where the arena actually begins... but I'm still not entirely sure
    uintptr_t curr_ptr = (uintptr_t)arena->buffer + (uintptr_t)arena->current_offset;
    uintptr_t offset = align_forward(curr_ptr, align); // How create `align` before actually calling the function? I thought that was the point of `align_forward`?
    offset -= (uintptr_t)arena->buffer; // Change to relative offset (Pretty certain he means relative to the previous offset)

    // Check to see if the backing memory has space left
    if (offset+size <= arena->buffer_length) {
        void *ptr = &arena->buffer[offset]; // Find the location of the current offset
        arena->previous_offset = offset;
        arena->current_offset = offset+size;

        // Zero new memory by default
        memset(ptr, 0, size);
        return ptr;
    }

    // Return NULL if the arena is out of memory
    return NULL;
}
