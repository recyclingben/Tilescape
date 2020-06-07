#pragma once
#include <stdint.h>
#include <biglist/list.h>

#include "place.h"


typedef struct {
    uint8_t type;
} ts_Tile;

typedef struct {
    ts_Tile tiles[(uint8_t)~0 + 1]
                 [(uint8_t)~0 + 1];
} ts_Blob;

typedef struct {
    index_Index2D *blobs;
    table_Table *robots;
} ts_World;

typedef struct {
    ts_Place place_x;
    ts_Place place_y;
} ts_Robot;