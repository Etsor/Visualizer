#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

#include "raylib.h"
#include "constants.h"
#include "sorts.h"
#include "utils.h"

int main(void) 
{
    srand((unsigned)time(NULL));

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Visualizer");
    SetTargetFPS(144);


    Shader bloom = 
        LoadShader(0, TextFormat("res/shaders/bloom.fs", GLSL_VERSION));
    
    RenderTexture2D target = 
        LoadRenderTexture(SCREEN_WIDTH, SCREEN_HEIGHT);


    InitAudioDevice();
    Sound sound_array[MAX_SOUNDS] = { 0 };
    sound_array[0] = LoadSound("res/sound.wav");
    SetSoundVolume(sound_array[0], 0.1f);
    for (size_t s = 1; s < MAX_SOUNDS; ++s)
        sound_array[s] = LoadSoundAlias(sound_array[0]);
    int current_sound = 0;


    int16_t* arr = generate_array(EL_AMOUNT);
    SortState state = sort_state(BUBBLE_SORT, "Bubble Sort", arr);

    while (!WindowShouldClose()) {    
        BeginTextureMode(target);
        
            ClearBackground(BLACK);
            DrawRectangleGradientV(
                0, 0, 
                SCREEN_WIDTH, SCREEN_HEIGHT, 
                DARKPURPLE, DARKBLUE
            );

            for (size_t k = 0; k < EL_AMOUNT; ++k) {
                Color color = 
                    (k == state.i || k == state.j) 
                    ? ACTIVE_COLOR : EL_TOP_COLOR; 
                
                DrawRectangleGradientV(
                    k * EL_WIDTH, 0, 
                    EL_WIDTH, arr[k], 
                    color, EL_BOTTOM_COLOR
                );
            }

            int swaps_done = 0;
            bool sound_played = false;
            
            if (IsKeyPressed(KEY_ONE)) 
                sort_state(BUBBLE_SORT, "Bubble Sort", arr);
            if (IsKeyPressed(KEY_TWO)) 
                sort_state(INSERTION_SORT, "Insertion Sort", arr);
            if (IsKeyPressed(KEY_THREE)) 
                sort_state(SELECTION_SORT, "Selection Sort", arr);
            if (IsKeyPressed(KEY_FOUR)) 
                sort_state(BOGO_SORT, "Bogo Sort", arr);

            if (IsKeyPressed(KEY_SPACE)) 
                state.paused = !state.paused;

            if (IsKeyPressed(KEY_UP)) {
                state.swaps_per_frame = MIN(
                    state.swaps_per_frame + SPEED_CHANGE_STEP, 
                    MAX_SWAPS_PER_FRAME
                );
            }

            if (IsKeyPressed(KEY_DOWN)) {
                state.swaps_per_frame = MAX(
                    state.swaps_per_frame - SPEED_CHANGE_STEP, 
                    MIN_SWAPS_PER_FRAME
                );
            }

            if (IsKeyPressed(KEY_R)) {
                free(arr);
                arr = generate_array(EL_AMOUNT);
                state.arr = arr;
                state.sorted = false;
                state.i = 0;
                state.j = 0;
            }

            while (!state.sorted && !state.paused && 
                   swaps_done < state.swaps_per_frame) {
                
                switch (state.current_sort) {
                    case BUBBLE_SORT:
                        bubble_sort(
                            &state, &swaps_done, 
                            &sound_played, sound_array, 
                            &current_sound
                        );
                        
                        break;
                    
                    case INSERTION_SORT:
                        insertion_sort(
                            &state, &swaps_done, 
                            &sound_played, sound_array, 
                            &current_sound
                        );
                        
                        break;
                    
                    case SELECTION_SORT:
                        selection_sort(
                            &state, &swaps_done, 
                            &sound_played, sound_array, 
                            &current_sound
                        );
                        
                        break;
                    
                    case BOGO_SORT:
                        bogo_sort(
                            &state, &swaps_done, 
                            &sound_played, sound_array, 
                            &current_sound
                        );
                        
                        break;
                    
                    default:
                        break;
                }
            }

        EndTextureMode();

        BeginDrawing();
            ClearBackground(BLACK);
            
            BeginShaderMode(bloom);
            
                DrawTextureRec(
                    target.texture, 
                    (Rectangle) { 
                        0, 0, 
                        (float) target.texture.width, 
                        (float)-target.texture.height 
                    },
                    (Vector2) { 0, 0 },
                    WHITE
                );
            
            EndShaderMode();
            
            DrawText( 
                HELP_TEXT,
                SCREEN_WIDTH - 190, 10, 
                20, 
                WHITE
            );
            
            DrawText(
                state.sort_name, 
                10, 10, 
                20, 
                WHITE
            );
            
            DrawText(
                TextFormat("Speed: %d", state.swaps_per_frame),
                10, 40, 
                20, 
                WHITE
            );
            
            DrawText(
                state.paused ? "PAUSED" : "",
                10, 70, 
                20, 
                RED
            );
        
        EndDrawing();
    }

    free(arr);
    
    UnloadShader(bloom);
    UnloadRenderTexture(target); 

    for (int i = 1; i < MAX_SOUNDS; i++) 
        UnloadSoundAlias(sound_array[i]);
    UnloadSound(sound_array[0]);
    CloseAudioDevice();
    
    CloseWindow();

    return 0;
}


