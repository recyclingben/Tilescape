#pragma once

#include "world_def.h"


ts_Place ts_robot_get_place_x(ts_Robot *robot)
{
    return robot->place_x;
}

ts_Place ts_robot_get_place_y(ts_Robot *robot)
{
    return robot->place_y;
}