#pragma once

#include <pebble.h>

#define LuigiBig_Stand 0
#define LuigiBig_Walk0 1
#define LuigiBig_Walk1 2
#define LuigiBig_Walk2 3
#define LuigiFire_Stand 4
#define LuigiFire_Walk0 5
#define LuigiFire_Walk1 6
#define LuigiFire_Walk2 7
#define LuigiSmall_Stand 8
#define LuigiSmall_Walk0 9
#define LuigiSmall_Walk1 10
#define LuigiSmall_Walk2 11
#define MarioBig_Stand 12
#define MarioBig_Walk0 13
#define MarioBig_Walk1 14
#define MarioBig_Walk2 15
#define MarioFire_Stand 16
#define MarioFire_Walk0 17
#define MarioFire_Walk1 18
#define MarioFire_Walk2 19
#define MarioSmall_Stand 20
#define MarioSmall_Walk0 21
#define MarioSmall_Walk1 22
#define MarioSmall_Walk2 23
#define MarioWeird_Stand 24
#define MarioWeird_Walk0 25
#define MarioWeird_Walk1 26
#define MarioWeird_Walk2 27

uint8_t SPRITE_DATA[][8] = {
    // {x, y, vram tile start, attributes, width, height, mosaic x, mosaic y}
    {0, 0, 0, 0b00000000, 1, 2, 0, 0}, // LuigiBig_Stand
    {0, 0, 8, 0b00000000, 1, 2, 0, 0}, // LuigiBig_Walk0
    {0, 0, 16, 0b00000000, 1, 2, 0, 0}, // LuigiBig_Walk1
    {0, 0, 24, 0b00000000, 1, 2, 0, 0}, // LuigiBig_Walk2
    {0, 0, 32, 0b00000000, 1, 2, 0, 0}, // LuigiFire_Stand
    {0, 0, 40, 0b00000000, 1, 2, 0, 0}, // LuigiFire_Walk0
    {0, 0, 48, 0b00000000, 1, 2, 0, 0}, // LuigiFire_Walk1
    {0, 0, 56, 0b00000000, 1, 2, 0, 0}, // LuigiFire_Walk2
    {0, 0, 64, 0b00000000, 1, 1, 0, 0}, // LuigiSmall_Stand
    {0, 0, 68, 0b00000000, 1, 1, 0, 0}, // LuigiSmall_Walk0
    {0, 0, 72, 0b00000000, 1, 1, 0, 0}, // LuigiSmall_Walk1
    {0, 0, 76, 0b00000000, 1, 1, 0, 0}, // LuigiSmall_Walk2
    {0, 0, 80, 0b00000000, 1, 2, 0, 0}, // MarioBig_Stand
    {0, 0, 88, 0b00000000, 1, 2, 0, 0}, // MarioBig_Walk0
    {0, 0, 96, 0b00000000, 1, 2, 0, 0}, // MarioBig_Walk1
    {0, 0, 104, 0b00000000, 1, 2, 0, 0}, // MarioBig_Walk2
    {0, 0, 112, 0b00000000, 1, 2, 0, 0}, // MarioFire_Stand
    {0, 0, 120, 0b00000000, 1, 2, 0, 0}, // MarioFire_Walk0
    {0, 0, 128, 0b00000000, 1, 2, 0, 0}, // MarioFire_Walk1
    {0, 0, 136, 0b00000000, 1, 2, 0, 0}, // MarioFire_Walk2
    {0, 0, 144, 0b00000000, 1, 1, 0, 0}, // MarioSmall_Stand
    {0, 0, 148, 0b00000000, 1, 1, 0, 0}, // MarioSmall_Walk0
    {0, 0, 152, 0b00000000, 1, 1, 0, 0}, // MarioSmall_Walk1
    {0, 0, 156, 0b00000000, 1, 1, 0, 0}, // MarioSmall_Walk2
    {0, 0, 160, 0b00000000, 1, 2, 0, 0}, // MarioWeird_Stand
    {0, 0, 168, 0b00000000, 1, 2, 0, 0}, // MarioWeird_Walk0
    {0, 0, 176, 0b00000000, 1, 2, 0, 0}, // MarioWeird_Walk1
    {0, 0, 184, 0b00000000, 1, 2, 0, 0}, // MarioWeird_Walk2
};