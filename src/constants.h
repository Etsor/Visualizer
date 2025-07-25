#ifndef CONSTANTS_H
#define CONSTANTS_H

#define GLSL_VERSION            330

#define SCREEN_WIDTH            1600
#define SCREEN_HEIGHT           1000

#define EL_AMOUNT               1600    // amount of elements in array
#define EL_WIDTH                1       // width of 1 element in visualization (pixels) 
#define EL_TOP_COLOR            BLANK   // top color of element in visualization (BLANK - transparent)
#define EL_BOTTOM_COLOR         BLACK   // bottom color of element in visualization
#define ACTIVE_COLOR            WHITE   // color of current active element

#define SWAPS_PER_FRAME         15      // amount of swaps in array per frame
#define MIN_SWAPS_PER_FRAME     1
#define MAX_SWAPS_PER_FRAME     100
#define SPEED_CHANGE_STEP       5

#define MAX_SOUNDS              4       // max amount of sounds that can play at the same time  

#define HELP_TEXT               "1.  Bubble Sort    \
                                \n2. Insertion Sort \
                                \n3. Selection Sort \
                                \n4. Bogo Sort      \
                                \nR. Reload         \
                                \nSPACE. Pause      \
                                \nUP/DOWN. Speed    \
                                \nESC. Exit"

#endif