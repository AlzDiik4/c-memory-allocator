#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>

typedef struct {
    uint8_t *buffer;
    size_t capacity;
    size_t offset;
} Arena;

Arena arena_init(size_t capacity) {
    Arena a;
    a.buffer = (uint8_t *)malloc(capacity);
    a.capacity = capacity;
    a.offset = 0;
    return a;
}

void *arena_alloc(Arena *a, size_t size) {
    // Align allocations to 8 bytes for hardware alignment
    size_t aligned_size = (size + 7) & ~7;

    if (a->offset + aligned_size > a->capacity) {
        fprintf(stderr, "Arena Out of Memory!\n");
        return NULL;
    }

    void *ptr = &a->buffer[a->offset];
    a->offset += aligned_size;
    return ptr;
}

void arena_reset(Arena *a) {
    a->offset = 0;
}

void arena_free(Arena *a) {
    free(a->buffer);
    a->buffer = NULL;
    a->capacity = 0;
    a->offset = 0;
}

int main() {
    Arena arena = arena_init(1024 * 1024); // Allocate 1MB region

    int *numbers = (int *)arena_alloc(&arena, 5 * sizeof(int));
    for (int i = 0; i < 5; i++) {
        numbers[i] = (i + 1) * 10;
        printf("numbers[%d] = %d\n", i, numbers[i]);
    }

    printf("Used arena memory: %zx bytes\n", arena.offset);

    arena_reset(&arena); // Zero-cost O(1) linear reset
    printf("Memory reset successfully.\n");

    arena_free(&arena);
    return 0;
}