#ifndef COLLATZ_H
#define COLLATZ_H

//Make sure to ALWAYS have even size for array
#define Max_array_size 100

unsigned long long cache_hits = 0;
unsigned long long cache_misses = 0;
unsigned long long array_size = 0;
unsigned long long index_array[Max_array_size] = {0};  //Array of zeroes
unsigned long long cache_array[Max_array_size] = {0};
unsigned long long policy_array[Max_array_size] = {0};

//Function pointer
typedef unsigned long long (*CacheMethod) (unsigned long long rand_num);

unsigned long long collatz_provider(unsigned long long rand_num);

unsigned long long collatz_rr(unsigned long long rand_num);

unsigned long long collatz_lru(unsigned long long rand_num);


#endif /* COLLATZ_H */