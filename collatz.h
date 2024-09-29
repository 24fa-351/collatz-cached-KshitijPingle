//Kshitij Pingle
//CWID: 885626978
//CPSC 351
//Assignment 4 - Collatz Conjecture
//28 September 2024

#ifndef COLLATZ_H
#define COLLATZ_H

#define Max_array_size 100

unsigned long long cache_hits = 0;
unsigned long long cache_misses = 0;
unsigned long long array_size = 0;


// Note: index_array and cache_array contain correspondingly matching elements
    // index_array[n] = Number
    // cache_array[n] = step count for Collatz Conjecture for the number
unsigned long long index_array[Max_array_size] = {0};
unsigned long long cache_array[Max_array_size] = {0};


// policy_array is used to manage LRU cache policy
unsigned long long policy_array[Max_array_size] = {0};

//Function pointer
typedef unsigned long long (*CacheMethod) (unsigned long long rand_num);

unsigned long long collatz_provider(unsigned long long rand_num);

unsigned long long collatz_rr(unsigned long long rand_num);

unsigned long long collatz_lru(unsigned long long rand_num);


#endif /* COLLATZ_H */