#pragma once
#include "world_def.h"


static inline void ts_blob_make(ts_Blob *blob,
                                ts_Blob **out_blob)
{
    *out_blob = malloc(sizeof(ts_Blob));
    memcpy(*out_blob, blob, sizeof(ts_Blob));
}

static inline void ts_blob_free(ts_Blob *blob)
{
    free(blob);
}

static inline void ts_blob_get_tile(ts_Blob *blob,
                                    uint8_t x,
                                    uint8_t y,
                                    ts_Tile **out_tile)
{
    *out_tile = &blob->tiles[x][y];
}