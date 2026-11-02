#ifndef ARENA_H
#define ARENA_H

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <assert.h>

// We use `char` since it's ubiquitous as meaning "as block of memory" (8 bytes on your current Apple M4 architecture)
typedef unsigned char byte;

// Personally, I'm a big fan of fully typing out variable names
// (for the most part)
typedef struct {
    byte *buffer;
    size_t buffer_length;
    size_t previous_offset;
    size_t current_offset;
} Arena;

#endif
