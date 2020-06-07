#pragma once

#include "world_def.h"


void ts_blob_get_tile(ts_Blob *blob,
                      uint8_t x,
                      uint8_t y,
                      ts_Tile **out_tile)
{
    *out_tile = &blob->tiles[x][y];
}