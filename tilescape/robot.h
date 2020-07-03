#pragma once
#include "world_def.h"


static inline ts_Place ts_robot_get_place_x(ts_Robot *robot)
{
    return robot->place_x;
}

static inline ts_Place ts_robot_get_place_y(ts_Robot *robot)
{
    return robot->place_y;
}

static inline void ts_robot_get_controller(ts_Robot *robot,
                                           ts_Controller **out_controller)
{
    *out_controller = &robot->controller;
}