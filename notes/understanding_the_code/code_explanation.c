#include <stdio.h>
#include <stdint.h>

#include "arena.h"

int main(void) {
    /////////////////////////////////////////////////////////////////////
    // Some introductory examples to help me get started
    printf("----------------FIRST EXAMPLES----------------\n");
    first_examples();
    printf("------------END OF FIRST EXAMPLES-------------\n");
    printf("\n\n\n");
    /////////////////////////////////////////////////////////////////////
    // Using the introductory examples as a foundation, convert the
    // operations into reusable functions before moving onto alignment

    // First, we initialize an empty arena
    Arena arena = {0};
    byte backing_buffer[16] = {0};
    size_t backing_buffer_size = sizeof(backing_buffer);
    arena = arena_init(&arena, *backing_buffer, backing_buffer_size);
    /////////////////////////////////////////////////////////////////////

    return 0;
}

void arena_print(Arena a, char *message) {
    printf("%s\n", message);
    printf("Starting address of the arena: %p\n", a.buffer);
    printf("Ending address of the arena:   %p\n", a.buffer + a.buffer_length - 1);
    printf("Size of the arena:             %zu byte(s)\n", a.buffer_length);
    printf("Previous offset:               %zu byte(s)\n", a.previous_offset);
    printf("Current offset:                %zu byte(s)\n", a.current_offset);
    printf("Values contained in the arena:");
    for (int i = 0; i < a.buffer_length; i++) {
        printf(" %i,", a.buffer[i]);
    }
    printf("\n\n");
}

void first_examples() {
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



    // Now let's practice using the previous offset field by filling another
    // quarter of the arena. This time we'll fill it with 2s
    for (size_t i = arena.current_offset; i < arena_quarter+arena.current_offset; i++) {
        arena.buffer[i] = 2;
    }
    arena.previous_offset = arena.current_offset;
    arena.current_offset = arena_quarter + arena.current_offset;
    arena_print(arena, "HALF FILLED ARENA:");
}

// Before moving onto alignment, let's see if we can convert these
// previous operations into functions

// First, we need an `arena_init` function
Arena arena_init(Arena *a, byte backing_buffer, size_t backing_buffer_size) {

}
