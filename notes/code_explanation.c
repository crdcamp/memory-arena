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

void arena_print(Arena *a) {
    printf("Starting address of the arena (`buffer`): %p\n", a->buffer);
    printf("Size of the arena (`buffer_length`):      %zu byte(s)\n", a->buffer_length);
    printf("`previous_offset`:                        %zu byte(s)\n", a->previous_offset);
    printf("`current_offset`:                         %zu byte(s)\n", a->current_offset);
}

int main(void) {
    // Let's begin by defining a pointer variable that indicates where the arena begins in memory
    // We define a backing buffer to give a start location for the arena to point to
    // As a result, we can also derive the arena's size by this backing buffer
    byte backing_buffer[256];
    byte *arena_start = backing_buffer;

    // Now let's create an example length of bytes for the arena
    // Remember that `size_t` is size in bytes
    size_t arena_size = sizeof(backing_buffer);

    // Obviously, there is no `previous_offset` or `current_offset`
    // yet since we haven't assigned anything to the arena yet
    // (or even actually created it yet)

    // Now let's create an example arena struct using `arena_start` and `arena_size`
    Arena *arena = {0}; // Initialize an empty struct
    arena->buffer = arena_start; // Define where the arena begins
    arena->buffer_length = arena_size; // Define how large the arena is

    // Initialize the previous and current offset as 0 for now
    arena->previous_offset = (size_t)arena_start;
    arena->current_offset = (size_t)arena_start;

    // Now let's take a look at the memory addresses of the arena in its current state
    arena_print(arena);

    return 0;
}
