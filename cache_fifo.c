#include "cache.h"   
#include <stdlib.h>  
#include <stdio.h>   

static void free_entry(CacheEntry *entry); // Helper function to free a cache entry

void cache_put(Cache* cache, int rod_length, int *cuts, int total_value, int *usage_count, int piece_count)
{
    if (cache->size == cache->capacity) {
        // Evict oldest entry (FIFO: Remove from front)
        free_entry(&cache->entries[cache->front]);
        cache->front = (cache->front + 1) % CACHE_CAPACITY;
        cache->size--;
    }

    // Insert at the rear position
    cache->entries[cache->rear].rod_length = rod_length;
    cache->entries[cache->rear].total_value = total_value;
    cache->entries[cache->rear].cuts = cuts;

    // Store usage counts
    cache->entries[cache->rear].usage_count = (int*)malloc(piece_count * sizeof(int));
    if (!cache->entries[cache->rear].usage_count) {
        fprintf(stderr, "Memory allocation failed in cache_put.\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < piece_count; i++) {
        cache->entries[cache->rear].usage_count[i] = usage_count[i];
    }

    // Move rear forward (circular queue)
    cache->rear = (cache->rear + 1) % CACHE_CAPACITY;
    cache->size++;
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
