#pragma once
#include "../world_def.h"
#include "engine_l1.h"
#include "engine_l2.h"


void ts_engine_l3_step(ts_World *world)
{
    ts_Robot *robot;

    table_head(world->robots, &robot);
    while (robot) {
        ts_engine_l2_push_robot_x(world, robot, 19);
        ts_engine_l2_push_robot_y(world, robot, 20);
        table_next(world->robots, robot, &robot);
    }
}