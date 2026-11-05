#include <stdio.h>
#include <stdint.h>


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
    size_t previous_offset; // The memory address of where the arena's used memory previously ended (I believe this is so you can reset the arena to it's last used location)
    size_t current_offset; // The memory address of where the arena's used memory ends
} Arena;

void arena_print(Arena a, char *message);
void first_examples();
void arena_init(Arena *arena, void *buffer, size_t buffer_len);

void arena_free(Arena *arena);

#endif
