#pragma once
#include "world_def.h"


static inline void ts_robot_get_key(ts_Robot *robot,
                                    uint32_t *out_key)
{
    *out_key = robot->key;
}

static inline ts_Place ts_robot_get_place_x(ts_Robot *robot)
{
    return robot->place_x;
}

static inline ts_Place ts_robot_get_place_y(ts_Robot *robot)
{
    return robot->place_y;
}