#pragma once
#include "../world_def.h"


void ts_engine_l1_move_robot_x(ts_Robot *robot,
                               uint8_t distance)
{
    robot->place_x.int_32 += distance;
}

void ts_engine_l1_move_robot_y(ts_Robot *robot,
                               uint8_t distance)
{
    robot->place_y.int_32 += distance;
}