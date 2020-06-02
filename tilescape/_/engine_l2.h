#pragma once
#include "../world_def.h"
#include "engine_l1.h"


void ts_engine_l2_push_robot_x(ts_World *world,
                               ts_Robot *robot,
                               uint8_t distance)
{
    ts_engine_l1_move_robot_x(robot, distance);
}

void ts_engine_l2_push_robot_y(ts_World *world,
                               ts_Robot *robot,
                               uint8_t distance)
{
    ts_engine_l1_move_robot_y(robot, distance);
}