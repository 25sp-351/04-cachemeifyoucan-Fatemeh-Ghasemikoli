#ifndef CACHE_H
#define CACHE_H

#include "pieces.h"

#define CACHE_CAPACITY 10

/**
 * Structure to hold cache entries
 */
typedef struct {
    int rod_length;   /**< Length of the rod */
    int total_value;  /**< Total value obtained from the best cuts */
    int *cuts;        /**< Array of cuts for the rod */
    int *usage_count; /**< Tracks how many times each piece was used */
} CacheEntry;

/**
 * Cache structure for both FIFO and LRU caching
 */
typedef struct Cache {
    int size; // Current number of elements in cache
    int capacity; // Maximum cache size
    int front;  // NEW: Tracks the oldest element for FIFO
    int rear;   // NEW: Tracks the next available position for FIFO
    CacheEntry entries[CACHE_CAPACITY]; // Array to store cache entries
} Cache;

/* Function declarations for managing the cache */
Cache* cache_create();   
void cache_destroy(Cache* cache);   
void cache_put(Cache* cache, int rod_length, int *cuts, int total_value, int *usage_count, int piece_count);
CacheEntry* cache_get(Cache* cache, int rod_length);

#endif // CACHE_H
