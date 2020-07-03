#pragma once
#include <stdint.h>
#include <biglist/list.h>

#include "place.h"


typedef struct {
    uint8_t type;
} ts_Tile;

typedef struct {
    ts_Tile tiles[(uint8_t)~0 + 1][(uint8_t)~0 + 1];
} ts_Blob;

typedef struct {
    uint8_t tick;
    index_Index2D *blobs;
    table_Table *robots;
} ts_World;

typedef struct {
    bool jump;
    bool jump_finish;
    bool push_n;
    bool push_s;
    bool push_e;
    bool push_w;
} ts_Controller;

typedef struct {
    int8_t velocity_x;
    int8_t velocity_y;
    ts_Place place_x;
    ts_Place place_y;
    ts_Controller controller;
} ts_Robot;