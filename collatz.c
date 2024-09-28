//Kshitij Pingle
//CWID: 885626978
//CPSC 351
//Assignment 4 - Collatz Conjecture
//17 September 2024

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "collatz.h"

//Collatz Conjecture function
unsigned long long collatz_provider(unsigned long long rand_num) {

    unsigned long long count = 0;

    //Start Collatz Conjecture
    while (1) {

        //DEBUGING:
        if (rand_num == 0) {
            printf("\n\nDEBUGING: Rand Num = 0\n\n");
            return count;
        }

        //Break statement
        if (rand_num == 1) {
            //printf("\n\nDebug: Rand num is %llu\n\n", rand_num);
            break;
        }
        else if ((rand_num % 2) == 0) {
            //num is even
            rand_num = rand_num / 2;
        }
        else {
            //num is odd
            rand_num = (3 * rand_num) + 1;
        }
        
        ++count;
    }

    return count;
}

//Least Recently Used Caching function
unsigned long long collatz_lru(unsigned long long num) {

    //Check if we already have value in array
    for (unsigned long long i = 0; i < array_size; ++i) {
        //printf("\nDEBUG : For loop executed %llu times", i);

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

    //We didn't find it in array, calculate it
    cache_misses++;

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
        cache_array[last_elem_pos] = step_count;        //cache_array and index_array should always be correspondingly arranged

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
unsigned long long collatz_rr(unsigned long long rand_num) {

    unsigned long long count = 0;
    unsigned long long rand_num_2 = 0;

    //Check if we already have it
    for(unsigned long long i = 0; i < sizeof(cache_array); ++i) {

        printf("\nDEBUG : Made it till here : 'i' is %llu, size of cache array : %lu\n\n", i, sizeof(cache_array));

        if (rand_num == cache_array[i]) {
            return index_array[i];
        }

        printf("Made it after if");
    } //This for loop will take O(n); n = Max_array_size

    //If we haven't found it, call collatz
    count = collatz_provider(rand_num);

    //Save to cache_array
    if (array_size == Max_array_size) {
        //Since array is full, start evicting
        //Defualt Policy : LRU (Least Recently Used)
        //My CWID: 88569678 - RR (Random Replacement)

        //Get Even Random Number for RR
        rand_num_2 = (rand() % ((Max_array_size - 2) + 1)) * 2; //'Max_array_size - 2' is max to make sure we have space

        //Replace in cache array
        index_array[rand_num_2] = rand_num;
        cache_array[rand_num_2] = count;   //Collatz count for rand_num
    }
    else {
        //Array is not full

        index_array[array_size] = rand_num;
        cache_array[array_size] = count;

        ++array_size;
    }

    return count;
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

    //Set srand() for rand()
    srand(time(NULL));

    //Initialize cache method to LRU by default
    CacheMethod collatz = collatz_lru;


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

        unsigned long long num = rand_num;
        printf("\nRandom number is %llu\n", rand_num);

        //Call collatz function -Seg fault this line
        unsigned long long count = collatz(rand_num);

        

        printf("Collatz conjecture with %llu took %llu steps\n", rand_num, count);

        //Write to csv file
        fprintf(fptr, "%llu, %llu\n", rand_num, count);

        count = 0;
    }

    fclose(fptr);

    //Calculate hit percent
    double cache_hit_percent = (double) (cache_hits * 100) / n;

    printf("\nCache hits = %llu, Cache misses = %llu, N = %llu", cache_hits, cache_misses, n);

    printf("\n\nCache hit percent : %3.2lf", cache_hit_percent);

    return 0;
}