#include "utils.h"
#include <stdlib.h>

#include "constants.h"

long long rand_num(long long start, long long end) {
    return start + (long long)((double)rand() / 
                   (RAND_MAX + 1.0) * (end - start + 1));
}

int16_t* generate_array(uint16_t el_amount) {
    int16_t* arr = malloc(el_amount * sizeof(int16_t));
    if (!arr) exit(EXIT_FAILURE);
    
    for (size_t i = 0; i < el_amount; ++i) {
        arr[i] = (int16_t)rand_num(10, SCREEN_HEIGHT - 10);
    }

    return arr; 
}