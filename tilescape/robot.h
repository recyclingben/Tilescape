#pragma once

#include "world_def.h"


uint32_t ts_robot_get_place_x(ts_Robot *robot)
{
    return robot->place_x.int_32;
}

uint32_t ts_robot_get_place_y(ts_Robot *robot)
{
    return robot->place_y.int_32;
}