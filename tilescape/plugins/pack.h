#pragma once
#include <netinet/in.h>
#include "../place.h"
#include "../world_def.h"


static inline void ts_place_pack(ts_Place *place)
{
    place->int_32 = htonl(place->int_32);
}

static inline void ts_place_unpack(ts_Place *place)
{
    place->int_32 = ntohl(place->int_32);
}

static inline void ts_tile_pack(ts_Tile *tile)
{
}

static inline void ts_tile_unpack(ts_Tile *tile)
{
}

static inline void ts_blob_pack(ts_Blob *blob)
{
    for (int x = 0; x <= (uint8_t)~0; ++x)
    for (int y = 0; y <= (uint8_t)~0; ++y)
        ts_tile_pack(&blob->tiles[x][y]);
}

static inline void ts_blob_unpack(ts_Blob *blob)
{
    for (int x = 0; x <= (uint8_t)~0; ++x)
    for (int y = 0; y <= (uint8_t)~0; ++y)
        ts_tile_unpack(&blob->tiles[x][y]);
}

static inline void ts_robot_pack(ts_Robot *robot)
{
    ts_place_pack(&robot->place_x);
    ts_place_pack(&robot->place_y);
}