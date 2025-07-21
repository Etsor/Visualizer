#ifndef SORTS_H
#define SORTS_H

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include "raylib.h"

typedef enum {
    BUBBLE_SORT,
    SELECTION_SORT,
    INSERTION_SORT,
    BOGO_SORT,

} SortType;

typedef struct {
    size_t i;
    size_t j;
    bool sorted;
    bool paused;
    int swaps_per_frame;
    int16_t* arr;
    SortType current_sort;
    const char* sort_name;

} SortState;

void bubble_sort(SortState* state, int* swaps_done, 
                 bool* sound_played, Sound* sound_array, 
                 int* current_sound);

void selection_sort(SortState* state, int* swaps_done, 
                    bool* sound_played, Sound* sound_array, 
                    int* current_sound);

void insertion_sort(SortState* state, int* swaps_done, 
                    bool* sound_played, Sound* sound_array, 
                    int* current_sound);

void bogo_sort(SortState* state, int* swaps_done, 
               bool* sound_played, Sound* sound_array, 
               int* current_sound);

#endif