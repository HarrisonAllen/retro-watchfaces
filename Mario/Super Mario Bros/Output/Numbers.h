#pragma once

#include <pebble.h>

#define NUMBER_WIDTH 3
#define NUMBER_HEIGHT 5

uint8_t NUMBER_TILES[][15] = {
    { // 0
        34, 23, 35, 
        40, 18, 40, 
        40, 18, 40, 
        40, 18, 40, 
        44, 23, 46, 
    },
    { // 1
        18, 36, 18, 
        37, 41, 18, 
        18, 40, 18, 
        18, 40, 18, 
        37, 24, 39, 
    },
    { // 2
        37, 23, 35, 
        18, 18, 40, 
        34, 23, 43, 
        40, 18, 18, 
        44, 23, 39, 
    },
    { // 3
        37, 23, 35, 
        18, 18, 40, 
        37, 23, 41, 
        18, 18, 40, 
        37, 23, 46, 
    },
    { // 4
        38, 18, 36, 
        40, 18, 40, 
        44, 23, 41, 
        18, 18, 40, 
        18, 18, 47, 
    },
    { // 5
        34, 23, 39, 
        40, 18, 18, 
        44, 23, 35, 
        18, 18, 40, 
        37, 23, 46, 
    },
    { // 6
        34, 23, 39, 
        40, 18, 18, 
        45, 23, 35, 
        40, 18, 40, 
        44, 23, 46, 
    },
    { // 7
        37, 23, 35, 
        18, 18, 40, 
        18, 18, 40, 
        18, 18, 40, 
        18, 18, 47, 
    },
    { // 8
        34, 23, 35, 
        40, 18, 40, 
        45, 23, 41, 
        40, 18, 40, 
        44, 23, 46, 
    },
    { // 9
        34, 23, 35, 
        40, 18, 40, 
        44, 23, 41, 
        18, 18, 40, 
        37, 23, 46, 
    },
    { // :
        18, 18, 18, 
        18, 42, 18, 
        18, 18, 18, 
        18, 42, 18, 
        18, 18, 18, 
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
