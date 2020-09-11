#pragma once
#include <stdint.h>
#include <biglist/list.h>

#include "place.h"


typedef struct {
    uint8_t type;
} TSTile;

typedef struct {
    TSTile tiles[(uint8_t)~0 + 1][(uint8_t)~0 + 1];
} TSBlob;

typedef struct {
    uint8_t tick;
    Index2D *blobs;
    Index *robots;
    Table *robots_table;
} TSWorld;

typedef struct {
    bool jump;
    bool jump_finish;
    bool push_n;
    bool push_s;
    bool push_e;
    bool push_w;
} TSController;

typedef struct {
    uint32_t key;
    int8_t velocity_x;
    int8_t velocity_y;
    TSPlace place_x;
    TSPlace place_y;
    TSController controller;
} TSRobot;