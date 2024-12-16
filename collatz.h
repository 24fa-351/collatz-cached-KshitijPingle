// Kshitij Pingle
// CWID: 885626978
// CPSC 351
// Assignment 4 - Collatz Conjecture
// 28 September 2024

#ifndef COLLATZ_H
#define COLLATZ_H

#define Max_array_size 36500

unsigned int cache_hits = 0;
unsigned int cache_misses = 0;
unsigned int array_size = 0;

// Note: index_array and cache_array contain correspondingly matching elements
// index_array[n] = Number
// cache_array[n] = step count for Collatz Conjecture for the number
unsigned int index_array[Max_array_size] = {0};
unsigned int cache_array[Max_array_size] = {0};

// policy_array is used to manage LRU cache policy
unsigned int policy_array[Max_array_size] = {0};

// Function pointer
typedef unsigned int (*CacheMethod)(unsigned int rand_num);

unsigned int collatz_provider(unsigned int rand_num);

unsigned int collatz_rr(unsigned int rand_num);

unsigned int collatz_lru(unsigned int rand_num);

#endif /* COLLATZ_H */