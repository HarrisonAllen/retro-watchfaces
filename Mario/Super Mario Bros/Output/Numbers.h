#pragma once

#include <pebble.h>

#define NUMBER_WIDTH 3
#define NUMBER_HEIGHT 5

uint8_t NUMBER_TILES[][15] = {
    { // 0
        226, 215, 227, 
        232, 210, 232, 
        232, 210, 232, 
        232, 210, 232, 
        236, 215, 238, 
    },
    { // 1
        210, 228, 210, 
        229, 233, 210, 
        210, 232, 210, 
        210, 232, 210, 
        229, 216, 231, 
    },
    { // 2
        229, 215, 227, 
        210, 210, 232, 
        226, 215, 235, 
        232, 210, 210, 
        236, 215, 231, 
    },
    { // 3
        229, 215, 227, 
        210, 210, 232, 
        229, 215, 233, 
        210, 210, 232, 
        229, 215, 238, 
    },
    { // 4
        230, 210, 228, 
        232, 210, 232, 
        236, 215, 233, 
        210, 210, 232, 
        210, 210, 239, 
    },
    { // 5
        226, 215, 231, 
        232, 210, 210, 
        236, 215, 227, 
        210, 210, 232, 
        229, 215, 238, 
    },
    { // 6
        226, 215, 231, 
        232, 210, 210, 
        237, 215, 227, 
        232, 210, 232, 
        236, 215, 238, 
    },
    { // 7
        229, 215, 227, 
        210, 210, 232, 
        210, 210, 232, 
        210, 210, 232, 
        210, 210, 239, 
    },
    { // 8
        226, 215, 227, 
        232, 210, 232, 
        237, 215, 233, 
        232, 210, 232, 
        236, 215, 238, 
    },
    { // 9
        226, 215, 227, 
        232, 210, 232, 
        236, 215, 233, 
        210, 210, 232, 
        229, 215, 238, 
    },
    { // :
        210, 210, 210, 
        210, 234, 210, 
        210, 210, 210, 
        210, 234, 210, 
        210, 210, 210, 
    },
};

uint8_t NUMBER_ATTRS[][15] = {
    { // 0
        0b00000000, 0b00000000, 0b00000000, 
        0b00000000, 0b00000000, 0b00000000, 
        0b00000000, 0b00000000, 0b00000000, 
        0b00000000, 0b00000000, 0b00000000, 
        0b00000000, 0b00000000, 0b00000000, 
    },
    { // 1
        0b00000000, 0b00000000, 0b00000000, 
        0b00000000, 0b00000000, 0b00000000, 
        0b00000000, 0b00000000, 0b00000000, 
        0b00000000, 0b00000000, 0b00000000, 
        0b00000000, 0b00000000, 0b00000000, 
    },
    { // 2
        0b00000000, 0b00000000, 0b00000000, 
        0b00000000, 0b00000000, 0b00000000, 
        0b00000000, 0b00000000, 0b00000000, 
        0b00000000, 0b00000000, 0b00000000, 
        0b00000000, 0b00000000, 0b00000000, 
    },
    { // 3
        0b00000000, 0b00000000, 0b00000000, 
        0b00000000, 0b00000000, 0b00000000, 
        0b00000000, 0b00000000, 0b00000000, 
        0b00000000, 0b00000000, 0b00000000, 
        0b00000000, 0b00000000, 0b00000000, 
    },
    { // 4
        0b00000000, 0b00000000, 0b00000000, 
        0b00000000, 0b00000000, 0b00000000, 
        0b00000000, 0b00000000, 0b00000000, 
        0b00000000, 0b00000000, 0b00000000, 
        0b00000000, 0b00000000, 0b00000000, 
    },
    { // 5
        0b00000000, 0b00000000, 0b00000000, 
        0b00000000, 0b00000000, 0b00000000, 
        0b00000000, 0b00000000, 0b00000000, 
        0b00000000, 0b00000000, 0b00000000, 
        0b00000000, 0b00000000, 0b00000000, 
    },
    { // 6
        0b00000000, 0b00000000, 0b00000000, 
        0b00000000, 0b00000000, 0b00000000, 
        0b00000000, 0b00000000, 0b00000000, 
        0b00000000, 0b00000000, 0b00000000, 
        0b00000000, 0b00000000, 0b00000000, 
    },
    { // 7
        0b00000000, 0b00000000, 0b00000000, 
        0b00000000, 0b00000000, 0b00000000, 
        0b00000000, 0b00000000, 0b00000000, 
        0b00000000, 0b00000000, 0b00000000, 
        0b00000000, 0b00000000, 0b00000000, 
    },
    { // 8
        0b00000000, 0b00000000, 0b00000000, 
        0b00000000, 0b00000000, 0b00000000, 
        0b00000000, 0b00000000, 0b00000000, 
        0b00000000, 0b00000000, 0b00000000, 
        0b00000000, 0b00000000, 0b00000000, 
    },
    { // 9
        0b00000000, 0b00000000, 0b00000000, 
        0b00000000, 0b00000000, 0b00000000, 
        0b00000000, 0b00000000, 0b00000000, 
        0b00000000, 0b00000000, 0b00000000, 
        0b00000000, 0b00000000, 0b00000000, 
    },
    { // :
        0b00000000, 0b00000000, 0b00000000, 
        0b00000000, 0b00000000, 0b00000000, 
        0b00000000, 0b00000000, 0b00000000, 
        0b00000000, 0b00000000, 0b00000000, 
        0b00000000, 0b00000000, 0b00000000, 
    },
};
