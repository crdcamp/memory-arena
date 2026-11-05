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

void arena_print(Arena a, char *message) {
    printf("%s\n", message);
    printf("Starting address of the arena:            %p\n", a.buffer);
    printf("Ending address of the arena:              %p\n", a.buffer + a.buffer_length - 1);
    printf("Size of the arena:                        %zu byte(s)\n", a.buffer_length);
    printf("Previous offset:                          %zu\n", a.previous_offset);
    printf("Current offset:                           %zu\n", a.current_offset);
    printf("Values contained in the arena:           ");
    for (int i = 0; i < a.buffer_length; i++) {
        printf(" %i", a.buffer[i]);
    }
    printf("\n\n");
}

int main(void) {
    // Let's begin by defining a pointer variable that indicates where the arena begins in memory
    // We define a backing buffer to give a start location for the arena to point to
    // As a result, we can also derive the arena's size by this backing buffer
    byte backing_buffer[16] = {0}; // Initialize with 0s to avoid garbage values

    // Now let's create an example arena struct using `arena_start` and `arena_size`
    Arena arena = {0}; // Initialize an empty struct
    arena.buffer = backing_buffer; // Define where the arena begins
    size_t backing_buffer_length = sizeof(backing_buffer);
    arena.buffer_length = backing_buffer_length; // Define how large the arena is

    // Initialize the previous and current offset as 0 for now
    arena.previous_offset = 0;
    arena.current_offset = 0;

    // Now let's take a look at the memory addresses of the arena in its current state
    arena_print(arena, "INITIALIZED ARENA:");



    // I think it's time to start playing around with the arena now.
    // Let's begin by trying to manually fill let's say.... a quarter of the arena
    // We'll keep it simple for now and fill it with 1s
    size_t arena_quarter = arena.buffer_length / 4;
    for (size_t i = 0; i < arena_quarter; i++) {
        arena.buffer[i] = 1;
    }

    // Now let's update the current offset
    arena.current_offset = arena_quarter;
    arena_print(arena, "QUARTER FILLED ARENA:");



    // Finally, before moving onto memory alignment, let's fill another quarter
    // of the values with 2, and update the previous offset
    for (size_t i = arena.current_offset; i < arena_quarter + arena.current_offset; i++) {
        arena.buffer[i] = 2;
    }
    arena.previous_offset = arena.current_offset;
    arena.current_offset = arena_quarter + arena.current_offset;
    arena_print(arena, "HALF FILLED ARENA:");

    return 0;
}
