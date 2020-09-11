#pragma once
#include "world_def.h"


static inline void ts_blob_make(TSBlob *blob,
                                TSBlob **out_blob)
{
    *out_blob = malloc(sizeof(TSBlob));
    memcpy(*out_blob, blob, sizeof(TSBlob));
}

static inline void ts_blob_free(TSBlob *blob)
{
    free(blob);
}

static inline void ts_blob_get_tile(TSBlob *blob,
                                    uint8_t x,
                                    uint8_t y,
                                    TSTile **out_tile)
{
    *out_tile = &blob->tiles[x][y];
}