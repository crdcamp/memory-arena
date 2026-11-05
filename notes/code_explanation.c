#include <stdio.h>
#include <stdint.h>


#ifndef DEFAULT_ALIGNMENT
// We multiply by 2 to help ensure that all data types (including the larger ones)
// are able to be stored in the arena
// I believe you can adjust this value by removing the *2 if your data types
// don't require 16-byte alignment
#define DEFAULT_ALIGNMENT (2*sizeof(void *))
#endif

typedef unsigned char byte;

typedef struct Arena {
    byte *buffer; // The memory address of where the arena begins (note the pointer)
    size_t buffer_length; // The total size of the arena in bytes
    size_t previous_offset; // The memory address of where the arena's used memory previously ended (I believe this is so you can reset the arena to it's last used location)
    size_t current_offset; // The memory address of where the arena's used memory ends
} Arena;

void arena_print(Arena a) {
    int backing_buffer_last_element = sizeof(&a.buffer)/sizeof(a.buffer[0]) - 1;

    printf("Starting address of the arena (`buffer`): %p\n", a.buffer);
    printf("Ending address of the arena:              %p\n", &a.buffer[backing_buffer_last_element]);
    printf("Size of the arena:                        %zu byte(s)\n", a.buffer_length);
    printf("Previous offset:                          %zu\n", a.previous_offset);
    printf("Current offset:                           %zu\n", a.current_offset);
}

int main(void) {
    // Let's begin by defining a pointer variable that indicates where the arena begins in memory
    // We define a backing buffer to give a start location for the arena to point to
    // As a result, we can also derive the arena's size by this backing buffer
    byte backing_buffer[256];

    // Now let's create an example arena struct using `arena_start` and `arena_size`
    Arena arena = {0}; // Initialize an empty struct
    arena.buffer = backing_buffer; // Define where the arena begins
    size_t backing_buffer_length = sizeof(backing_buffer);
    arena.buffer_length = backing_buffer_length; // Define how large the arena is

    // Initialize the previous and current offset as 0 for now
    arena.previous_offset = 0;
    arena.current_offset = 0;

    // Now let's take a look at the memory addresses of the arena in its current state
    arena_print(arena);

    return 0;
}
