#ifndef UTILS_H
#define UTILS_H

#include <stdint.h>

#define MIN(a,b) ((a) < (b) ? (a) : (b))
#define MAX(a,b) ((a) > (b) ? (a) : (b))

long long rand_num(long long start, long long end);
int16_t* generate_array(uint16_t el_amount);

#endif