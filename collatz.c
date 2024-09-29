//Kshitij Pingle
//CWID: 885626978
//CPSC 351
//Assignment 4 - Collatz Conjecture
//28 September 2024

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "collatz.h"

//Collatz Conjecture function
unsigned long long collatz_provider(unsigned long long num) {

    unsigned long long step_count = 0;

    //Start Collatz Conjecture
    while (1) {

        if (num == 1) {
            break;
        }
        else if ((num % 2) == 0) {
            //num is even
            num = num / 2;
        }
        else {
            //num is odd
            num = (3 * num) + 1;
        }
        
        ++step_count;
    }

    return step_count;
}


//Least Recently Used Caching function
unsigned long long collatz_lru(unsigned long long num) {

    //Check if we already have value in array
    for (unsigned long long i = 0; i < array_size; ++i) {

        if (num == index_array[i]) {

            //Move elements all elements in policy array by one
            for (unsigned long long j = array_size; j > 0; --j) {
                policy_array[j] = policy_array[j - 1];
            }

            policy_array[0] = num;

            cache_hits++;

            return cache_array[i];
        }
    }

    cache_misses++;

    //We didn't find it in array, calculate it
    unsigned long long step_count = collatz_provider(num);

    if (array_size == Max_array_size) {

        unsigned long long last_elem_pos = 0;

        //Find position of last element from policy array in index array
        for (unsigned long long i = 0; i < array_size; ++i) {
            if (policy_array[array_size - 1] == index_array[i]) {
                last_elem_pos = i;
                break;
            }
        }

        index_array[last_elem_pos] = num;
        cache_array[last_elem_pos] = step_count;

        //Move all elements in policy array by one
        for (unsigned long long i = array_size; i > 0; --i) {
            policy_array[i] = policy_array[i - 1];
        }

        policy_array[0] = num;

    }
    else {
        //Array not full

        index_array[array_size] = num;
        cache_array[array_size] = step_count;

        //Move all elements in policy array by one
        for (unsigned long long i = array_size; i > 0; --i) {
            policy_array[i] = policy_array[i - 1];
        }

        policy_array[0] = num;

        ++array_size;
    }

    return step_count;
}


//Random Replacement Caching function
unsigned long long collatz_rr(unsigned long long num) {

    //Check if we already have it
    for(unsigned long long i = 0; i < array_size; ++i) {

        if (num == index_array[i]) {
            ++cache_hits;
            return cache_array[i];
        }
    }

    //We don't already have it, calculate it
    unsigned long long step_count = collatz_provider(num);

    ++cache_misses;

    if (array_size == Max_array_size) {
        //Evict a number at a random position

        //Get Random Position for RR
        unsigned long long rand_pos = rand() % ((array_size - 1) + 1); //'array_size - 1' is max to make sure we have space

        index_array[rand_pos] = num;
        cache_array[rand_pos] = step_count;
    }
    else {
        
        index_array[array_size] = num;
        cache_array[array_size] = step_count;

        ++array_size;
    }

    return step_count;
}

int main(unsigned long long argc, char *argv[]) {

    //Collect 3 arguments - N, Min, Max
    unsigned long long n = atoi(argv[1]);
    unsigned long long min = atoi(argv[2]);
    unsigned long long max = atoi(argv[3]);

    //Make file
    FILE *fptr = fopen("collatz.csv", "w+");     //'w+' means it will create it if it doesn't exist

    //Print header row in file
    fprintf(fptr, "Number, Steps\n");

    //Initialize cache method to LRU by default
    CacheMethod collatz = collatz_lru;

    if (argc > 3) {
        collatz = collatz_rr;
    }


    //Main loop
    for (unsigned long long i = 0; i < n; ++i) {

        unsigned long long rand_num = 0;

        //Loop to get rand_num (Don't want zeroes)
        while (1) {

            //Get random number within range
            rand_num = rand() % ((max - min + 1) - min);

            if(rand_num != 0) {
                break;
            }

        }

        //Call collatz function -Seg fault this line
        unsigned long long step_count = collatz(rand_num);

        // printf("Collatz conjecture with %llu took %llu steps\n", rand_num, step_count);

        //Write to csv file
        fprintf(fptr, "%llu, %llu\n", rand_num, step_count);

        step_count = 0;
    }

    fclose(fptr);

    double cache_hit_percent = (double) (cache_hits * 100) / n;

    printf("\nCache hits = %llu, Cache misses = %llu, N = %llu", cache_hits, cache_misses, n);

    printf("\nCache hit percent : %3.2lf\n", cache_hit_percent);

    return 0;
}