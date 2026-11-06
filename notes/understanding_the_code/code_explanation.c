#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "arena.h"

int main(void) {
    /////////////////////////////////////////////////////////////////////
    // Some introductory examples to help me get started
    //first_examples();
    /////////////////////////////////////////////////////////////////////



    /////////////////////////////////////////////////////////////////////
    // Using the introductory examples as a foundation, convert the
    // operations into reusable functions before moving onto alignment
    // First, we initialize an empty arena
    // Initialize with 0 and NULL values to avoid garbage values, although you'd think `arena_init` makes this unnecessary.
    Arena arena = {0};

    // Define some arrays for computing the arena's size
    int quarter_ones[4];
    int quarter_twos[4];
    int half_threes[8];
    size_t arena_size = sizeof(quarter_ones) + sizeof(quarter_twos) + sizeof(half_threes);

    byte buffer[arena_size];

    printf("Size of `arena_size`: %zu bytes\n", arena_size);
    printf("Size of `buffer`: %zu bytes\n", sizeof(buffer));

    size_t buffer_length = sizeof(buffer) / sizeof(buffer[0]);

    // Initialize
    arena_init(&arena, buffer, buffer_length); // Initialize an empty arena with a size of 16 bytes
    arena_print(&arena, "INITIALIZED ARENA:");


    // Now let's fill this arena with some basic integer arrays
    // We'll fill a quarter of the arena with 1s, another quarter
    // with 2s, and the last half with 3s
    int *ones = arena_alloc(&arena, sizeof(buffer) / 4);
    if (ones) {
        for (size_t i = 0; i < sizeof(quarter_ones) / sizeof(quarter_ones[0]); i++) {
            ones[i] = 1;
        }
    }
    arena_print(&arena, "ONES:");

    int *twos = arena_alloc(&arena, sizeof(buffer) / 4);
    if (twos) {
        for (size_t i = 0; i < sizeof(quarter_twos) / sizeof(quarter_twos[0]); i++) {
            twos[i] = 2;
        }
    }
    arena_print(&arena, "TWOS:");

    int *threes = arena_alloc(&arena, sizeof(buffer) / 2);
    if (threes) {
        for (size_t i = 0; i < sizeof(half_threes) / sizeof(half_threes[0]); i++) {
            threes[i] = 3;
        }
    }
    arena_print(&arena, "THREES:");

    arena_free(&arena);

    // Now let's quickly print the ones array
    printf("Quick check for ones values:");
    for (size_t i = 0; i < sizeof(quarter_ones) / sizeof(quarter_ones[0]); i++) {
        printf(" %i", ones[i]);
    }
    printf("\n");

    /////////////////////////////////////////////////////////////////////


    /////////////////////////////////////////////////////////////////////
    // Now we can FINALLY start investigating how memory alignment works
    // We'll also include a `free_arena` function, which involves simply resetting
    // the offsets of the arena to 0
    /////////////////////////////////////////////////////////////////////

    return 0;
}

void arena_print(Arena *a, char *message) {
    printf("%s\n", message);
    printf("Starting address of the arena: %p\n", a->buffer);
    printf("Ending address of the arena:   %p\n", a->buffer + a->buffer_length - 1);
    printf("Size of the arena:             %zu byte(s)\n", a->buffer_length);
    printf("Previous offset:               %zu byte(s)\n", a->previous_offset);
    printf("Current offset:                %zu byte(s)\n", a->current_offset);
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
    arena_print(&arena, "INITIALIZED ARENA:");



    // I think it's time to start playing around with the arena now.
    // Let's begin by trying to manually fill let's say.... a quarter of the arena
    // We'll keep it simple for now and fill it with 1s
    size_t arena_quarter = arena.buffer_length / 4;
    for (size_t i = 0; i < arena_quarter; i++) {
        arena.buffer[i] = 1;
    }

    // Now let's update the current offset
    arena.current_offset = arena_quarter;
    arena_print(&arena, "QUARTER FILLED ARENA:");



    // Now let's practice using the previous offset field by filling another
    // quarter of the arena. This time we'll fill it with 2s
    for (size_t i = arena.current_offset; i < arena_quarter+arena.current_offset; i++) {
        arena.buffer[i] = 2;
    }
    arena.previous_offset = arena.current_offset;
    arena.current_offset = arena_quarter + arena.current_offset;
    arena_print(&arena, "HALF FILLED ARENA:");
}

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

// Allocate memory to the arena
// I think this might be a bit messy, but it's a start
// THIS IS INCORRECT USAGE ANYWAY. YOU SHOULD BE RETURNING A POINTER
void *arena_alloc(Arena *arena, size_t size) {
    // TODO: Convert to an overflow-safe check
    // Check if the arena has enough available memory
    if (arena->current_offset + size <= arena->buffer_length) {
        // Set a pointer to where the new allocation begins
        void *ptr = &arena->buffer[arena->current_offset];
        // Set previous offset to current offset
        arena->previous_offset = arena->current_offset;
        // Set the current offset to the end of the newly allocated memory
        arena->current_offset = arena->current_offset + size;
        // Return the new start point for storing memory
        return ptr;
    }

    // If there isn't enough space left in the arena, return NULL
    return NULL;
}

void arena_free(Arena *arena) {
    arena->current_offset = 0;
    arena->previous_offset = 0;
}

bool is_power_of_two(uintptr_t x) {
    return (x & (x-1)) == 0;
}

uintptr_t align_forward(uintptr_t ptr, size_t align) {
    // We assign to these new values to avoid editing the
    // original pointer and to cast types
    uintptr_t p, a, modulo;

    // Determine if the alignment is valid
    // Might want to change this to something that isn't `assert()`
    assert(is_power_of_two(align));

    p = ptr;
    a = align;
    // Same as using `%`, but faster since a is a power of 2
    modulo = p & (a-1);
    // If there is a remainder, adjust the pointer forward to
    // an aligned spot in memory using the difference between
    // alignment and remainder
    if (modulo != 0) {
        p += a - modulo;
    }

    return p;
}

void *arena_alloc_align(Arena *arena, size_t size, size_t align) {
    // Align the pointer forward to the specified alignment
    // Set a pointer to the arena's current offset
    uintptr_t curr_ptr = (uintptr_t)arena->buffer + arena->current_offset;
    // Align the current offset forward to an aligned location
    uintptr_t offset = align_forward(curr_ptr, align);

    // Now that we've set the "offset" to an aligned location at or after
    // the arena's current offset, we now need to subtract the buffer's
    // location to find where the relative offset should be

    // align_forward returned an absolute address. Subtract the buffer's
    // address to convert it into an index relative to the buffer start,
    // which is the unit that current_offset, previous_offset, and
    // buffer[...] all use.

    // Think about it like this:
    // curr_ptr = buffer + current_offset
    // offset = curr_ptr + padding
    // offset - buffer = current offset + padding
    // current_offset is already accounted for, so that's why we subtract the buffer!
    offset -= (uintptr_t)arena->buffer; // Change to relative offset
    // Check to see if backing memory has space left
    if (offset+size <= arena->buffer_length) {
        // Set a pointer to where the new allocation begins
        void *ptr = &arena->buffer[offset];
        // Set the previous offset to the new offset
        arena->previous_offset = offset;
        // Set the current offset to the end of the newly allocated memory
        arena->current_offset = offset+size;
        // Return a pointer that marks where the newly allocated memory begins
        return ptr;
    }

    // If there's not enough memory left to allocate, return NULL;
    return NULL;
}
