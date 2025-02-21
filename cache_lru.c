#include "cache.h"  // Ensure this is included first
#include <stdlib.h>  // For malloc()
#include <stdio.h>   // For fprintf()

/* ---------------------- HELPER FUNCTION DECLARATIONS ------------------------ */
static int find_index_recursive(Cache* cache, int rod_length, int startIndex);
static void move_to_top(Cache* cache, int index);
static void shift_right(CacheEntry entries[], int fromIndex, int toIndex);
static void free_entry(CacheEntry *entry);

void cache_put(Cache* cache, int rod_length, int *cuts, int total_value, int *usage_count, int piece_count)
{
    int index = find_index_recursive(cache, rod_length, 0);
    if (index >= 0) {
        // If entry exists, update it
        free_entry(&cache->entries[index]);
        cache->entries[index].rod_length = rod_length;
        cache->entries[index].total_value = total_value;
        cache->entries[index].cuts = cuts;

        // Allocate memory for usage counts
        cache->entries[index].usage_count = (int*)malloc(piece_count * sizeof(int));
        if (!cache->entries[index].usage_count) {
            fprintf(stderr, "Memory allocation failed in cache_put.\n");
            exit(EXIT_FAILURE);
        }

        for (int i = 0; i < piece_count; i++) {
            cache->entries[index].usage_count[i] = usage_count[i];
        }

        move_to_top(cache, index);
        return;
    }

    // Cache is full → remove least recently used
    if (cache->size >= cache->capacity) {
        free_entry(&cache->entries[cache->size - 1]);
        shift_right(cache->entries, 0, cache->size - 1);
    }
    else {
        shift_right(cache->entries, 0, cache->size);
        cache->size++;
    }

    // Insert new entry
    cache->entries[0].rod_length = rod_length;
    cache->entries[0].total_value = total_value;
    cache->entries[0].cuts = cuts;

    // Store usage counts
    cache->entries[0].usage_count = (int*)malloc(piece_count * sizeof(int));
    if (!cache->entries[0].usage_count) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < piece_count; i++) {
        cache->entries[0].usage_count[i] = usage_count[i];
    }
}

/* ---------------------- FUNCTION DEFINITIONS ------------------------- */

/**
 * Recursively searches for rod_length in entries[startIndex..(size-1)].
 * Returns the index if found, or -1 if not found.
 */
static int find_index_recursive(Cache *cache, int rod_length, int startIndex)
{
    if (startIndex >= cache->size) {
        return -1; // Not found
    }
    if (cache->entries[startIndex].rod_length == rod_length) {
        return startIndex;
    }
    // Recurse to the next index
    return find_index_recursive(cache, rod_length, startIndex + 1);
}

/**
 * Moves the accessed cache entry to the front (index 0).
 * This ensures the most recently used entry is always at the front.
 */
static void move_to_top(Cache* cache, int index)
{
    if (index <= 0) {
        return; // Already at the front
    }
    CacheEntry temp = cache->entries[index];

    // Shift entries from 0 to index-1 right
    shift_right(cache->entries, 0, index - 1);

    // Place temp at index 0
    cache->entries[0] = temp;
}

/**
 * Shifts cache entries in the range [start, end] one position to the right.
 */
static void shift_right(CacheEntry entries[], int fromIndex, int toIndex)
{
    if (toIndex < fromIndex) {
        return;
    }
    entries[toIndex + 1] = entries[toIndex];

    shift_right(entries, fromIndex, toIndex - 1);
}

/**
 * Frees a cache entry by releasing dynamically allocated memory.
 */
static void free_entry(CacheEntry *entry)
{
    if (entry->cuts) {
        free(entry->cuts);
        entry->cuts = NULL;
    }
    if (entry->usage_count) {
        free(entry->usage_count);
        entry->usage_count = NULL;
    }
    entry->rod_length = -1;
    entry->total_value = 0;
}
