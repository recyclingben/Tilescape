#pragma once
#include <netinet/in.h>
#include "../place.h"
#include "../world_def.h"


static inline void ts_place_pack(TSPlace *place)
{
    place->int_32 = htonl(place->int_32);
}

static inline void ts_place_unpack(TSPlace *place)
{
    place->int_32 = ntohl(place->int_32);
}

static inline void ts_tile_pack(TSTile *tile)
{
}

static inline void ts_tile_unpack(TSTile *tile)
{
}

static inline void ts_blob_pack(TSBlob *blob)
{
    for (int x = 0; x <= (uint8_t)~0; ++x)
    for (int y = 0; y <= (uint8_t)~0; ++y)
        ts_tile_pack(&blob->tiles[x][y]);
}

static inline void ts_blob_unpack(TSBlob *blob)
{
    for (int x = 0; x <= (uint8_t)~0; ++x)
    for (int y = 0; y <= (uint8_t)~0; ++y)
        ts_tile_unpack(&blob->tiles[x][y]);
}

static inline void ts_robot_pack(TSRobot *robot)
{
    robot->key = htons(robot->key);
    ts_place_pack(&robot->place_x);
    ts_place_pack(&robot->place_y);
}

static inline void ts_robot_unpack(TSRobot *robot)
{
    robot->key = ntohs(robot->key);
    ts_place_unpack(&robot->place_x);
    ts_place_unpack(&robot->place_y);
}