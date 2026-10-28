#ifndef ARENA_H
#define ARENA_H

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <assert.h>

// Personally, I'm a big fan of fully typing out variable names
// (for the most part)
typedef struct {
    unsigned char *buffer;// We use `char` here for reasons I'm forgetting at the moment. I'm also a bit fuzzy on why we use a buffer. Is it just the starting pointer? If so, why the fuck are we calling it a buffer
    size_t buffer_length;
    size_t previous_offset;
    size_t current_offset; // The amount of memory currently used in the arena (might change to `usage` when I'm more comfortable)
} Arena;

bool is_power_of_two(uintptr_t x);
uintptr_t align_forward(uintptr_t ptr, size_t align);
void *arena_alloc_align(Arena *arena, size_t size, size_t align);

#endif
