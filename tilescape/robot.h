#pragma once
#include "world_def.h"


static inline void ts_robot_get_key(TSRobot *robot,
                                    uint32_t *out_key)
{
    *out_key = robot->key;
}

static inline TSPlace ts_robot_get_place_x(TSRobot *robot)
{
    return robot->place_x;
}

static inline TSPlace ts_robot_get_place_y(TSRobot *robot)
{
    return robot->place_y;
}