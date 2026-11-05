#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "arena.h"

int main(void) {
    /////////////////////////////////////////////////////////////////////
    // Some introductory examples to help me get started
    first_examples();
    /////////////////////////////////////////////////////////////////////
    // Using the introductory examples as a foundation, convert the
    // operations into reusable functions before moving onto alignment

    // First, we initialize an empty arena
    // Initialize with 0 and NULL values to avoid garbage values, although you'd think `arena_init` makes this unnecessary.
    // Make sure to test this above point later
    // Note that this can also not be created as a pointer and instead be passed as `&a` to `arena_init` to create a pointer
    // I think I prefer creating the arenas as pointers for now, but keep in mind function scopes and arena lifetimes when deciding on this
    Arena arena = {0};

    byte buffer[16]; // 16 bytes for simplicity
    size_t buffer_len = sizeof(buffer) / sizeof(buffer[0]);
    printf("Buffer length: %zu\n", buffer_len);

    arena_init(&arena, buffer, buffer_len); // Initialize an empty arena with a size of 16 bytes
    arena_print(arena, "INITIALIZED ARENA:");
    printf("Note: the arena is initialized with garbage values, since we only need to use memset when actually allocating the memory\n");

    // // Now let's fill this arena with some basic integer arrays
    // // We'll create two arrays that will fill a quarter of the arena,
    // // and one that fills half
    // size_t arena_quarter = sizeof(arena->buffer_length) / 4;
    // size_t arena_half = sizeof(arena->buffer_length) / 2;
    // printf("Quarter size: %zu\n", arena_quarter);
    // printf("Half size: %zu\n", arena_half);
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

// First, we need an `arena_init` function to initialize an empty arena of
// a desired size
// Bill uses `void` instead of a `byte` for `backing_buffer`. I prefer `byte` due
// to ensuring type consistency, but I have a feeling Bill's use of `void` is more correct
void arena_init(Arena *arena, void *buffer, size_t buffer_length) {
    // Initialize the buffer size and buffer length
    arena->buffer = buffer;
    arena->buffer_length = buffer_length;
    // Initialize the current and previous offset as 0,
    // since an empty arena has no use for them
    arena->previous_offset = 0;
    arena->current_offset = 0;
}
