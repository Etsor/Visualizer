#include <stdbool.h>
#include <stdlib.h>
#include "sorts.h"
#include "constants.h"

static bool is_sorted(int16_t* arr, size_t n) {
    for (size_t i = 1; i < n; ++i)
        if (arr[i-1] > arr[i]) return false;
    return true;
}

void bogo_sort(SortState* state, int* swaps_done, 
               bool* sound_played, Sound* sound_array, 
               int* current_sound) 
{
    if (is_sorted(state->arr, EL_AMOUNT)) {
        state->sorted = true;
        return;
    }
    for (size_t i = 0; i < EL_AMOUNT; ++i) {
        size_t j = rand() % EL_AMOUNT;
        int16_t tmp = state->arr[i];
        state->arr[i] = state->arr[j];
        state->arr[j] = tmp;
    }
    if (!*sound_played) {
        SetSoundPitch(sound_array[*current_sound], 1.0f);
        PlaySound(sound_array[*current_sound]);
        *current_sound = (*current_sound + 1) % MAX_SOUNDS;
        *sound_played = true;
    }
    (*swaps_done)++;
}

void bubble_sort(SortState* state, int* swaps_done, 
                 bool* sound_played, Sound* sound_array, 
                 int* current_sound) 
{
    if (state->j < EL_AMOUNT) {
        if (state->i + 1 < EL_AMOUNT) {
            if (state->arr[state->i] > state->arr[state->i + 1]) {
                if (!*sound_played) {
                    SetSoundPitch(sound_array[*current_sound], 
                                 (float)state->arr[state->i] / 300.0f);
                    PlaySound(sound_array[*current_sound]);
                    *current_sound = (*current_sound + 1) % MAX_SOUNDS;
                    *sound_played = true;
                }
                
                int16_t tmp = state->arr[state->i];
                state->arr[state->i] = state->arr[state->i + 1];
                state->arr[state->i + 1] = tmp;
            }
        
            state->i++;
            (*swaps_done)++;
        
        } else {
            state->i = 0;
            state->j++;
        }
 
    } else state->sorted = true;
}

void selection_sort(SortState* state, int* swaps_done, 
                    bool* sound_played, Sound* sound_array, 
                    int* current_sound) 
{
    if (state->i < EL_AMOUNT - 1) {
        size_t min_idx = state->i;
        for (size_t k = state->i + 1; k < EL_AMOUNT; k++) {
            if (state->arr[k] < state->arr[min_idx]) {
                min_idx = k;
            }
        }
        
        if (min_idx != state->i) {
            if (!*sound_played) {
                SetSoundPitch(sound_array[*current_sound], 
                             (float)state->arr[state->i] / 300.0f);
                PlaySound(sound_array[*current_sound]);
                *current_sound = (*current_sound + 1) % MAX_SOUNDS;
                *sound_played = true;
            }

            int16_t tmp = state->arr[state->i];
            state->arr[state->i] = state->arr[min_idx];
            state->arr[min_idx] = tmp;
        }
    
        state->i++;
        (*swaps_done)++;
    
    } else state->sorted = true;
}

void insertion_sort(SortState* state, int* swaps_done, 
                    bool* sound_played, Sound* sound_array, 
                    int* current_sound) 
{
    if (state->i < EL_AMOUNT) {
        if (state->j > 0 && state->arr[state->j - 1] > state->arr[state->j]) {
            if (!*sound_played) {
                SetSoundPitch(sound_array[*current_sound], 
                             (float)state->arr[state->j] / 300.0f);
                PlaySound(sound_array[*current_sound]);
                *current_sound = (*current_sound + 1) % MAX_SOUNDS;
                *sound_played = true;
            }

            int16_t tmp = state->arr[state->j];
            state->arr[state->j] = state->arr[state->j - 1];
            state->arr[state->j - 1] = tmp;
            state->j--;
        
        } else {
            state->i++;
            state->j = state->i;
        }
        
        (*swaps_done)++;
    
    } else state->sorted = true;
}