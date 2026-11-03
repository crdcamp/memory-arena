#ifndef ARENA_H
#define ARENA_H

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>

// We use `char` since it's ubiquitous as meaning "as block of memory" (8 bytes on your current Apple M4 architecture)
typedef unsigned char byte;

typedef struct Arena {
    byte *buffer; // Define an entry point for the arena
    size_t buffer_length;
    size_t previous_offset;
    size_t current_offset;
} Arena;

bool is_power_of_two(uintptr_t x);

#endif
