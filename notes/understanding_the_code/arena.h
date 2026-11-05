#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

#ifndef ARENA_H
#define ARENA_H
// We multiply by 2 to help ensure that all data types (including the larger ones)
// are able to be stored in the arena
// I believe you can adjust this value by removing the *2 if your data types
// don't require 16-byte alignment
#define DEFAULT_ALIGNMENT (2*sizeof(void *))

typedef unsigned char byte;

typedef struct Arena {
    byte *buffer; // The memory address of where the arena begins (note the pointer)
    size_t buffer_length; // The total size of the arena in bytes
    size_t previous_offset; // The memory address of where the arena's used memory previously ended
    size_t current_offset; // The memory address of where the arena's used memory ends
} Arena;

// Introductory lessons
void arena_print(Arena a, char *message);
void first_examples();

// Converting introductory lessons into functions
void arena_init(Arena *arena, void *buffer, size_t buffer_len);
void arena_alloc(Arena *arena, size_t size, int value);

// Implementing memory alignment
bool is_power_of_two(uintptr_t x);
uintptr_t align_forward(uintptr_t ptr, size_t align);
void arena_alloc_align(Arena *arena, size_t size, int value, size_t align);
void *arena_free(Arena *arena);

#endif
