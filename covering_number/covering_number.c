// script to find all the numbers x that cover a number l e.g. 
// if i start at 0 and keep adding x then modding by l i will eventually
// would have visited all numbers 1..l at some point.

#include <stdio.h>
#include <stdlib.h>
//gcc file.c -o executable


int main(){
    // Gather all factorions
    const int limit = 320;
    int current_index = 0;
    int * list;
    int size = 0;
    int capacity = 2;
    list = (int *)malloc(capacity * sizeof(int));
    int i;
    int current_number;
    int count;
    
    for (i = 0; i < limit; i++) {
        if(size == capacity){
            capacity *= 2;
            list = (int *)realloc(list, capacity * sizeof(int));
        }

        current_number = 0;
        count = 0;
        while(1){
            current_number += i;
            current_number = current_number % limit;
            count++;
            if(current_number == 0){
                break;
            }
        }

        if(count >= limit){
            list[size] = i;
            size++;
        }
    }

    for (i = 0; i < size; i++) {
        printf("Covered by: %i \n", list[i]);
        fflush( stdout );
    }

    free(list);

    return 0;
}



