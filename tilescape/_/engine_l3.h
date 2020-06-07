#pragma once
#include "../world_def.h"
#include "engine_l1.h"
#include "engine_l2.h"


void ts_engine_l3_step(ts_World *world)
{
    ts_Robot *robot;

    table_head(world->robots, &robot);
    while (robot) {
        /* We could do this without if statements but I doubt it would be faster. */
        if (robot->controller.push_n) ts_engine_l2_push_robot_y(world, robot, -4);
        if (robot->controller.push_s) ts_engine_l2_push_robot_y(world, robot,  4);
        if (robot->controller.push_e) ts_engine_l2_push_robot_x(world, robot,  4);
        if (robot->controller.push_w) ts_engine_l2_push_robot_x(world, robot, -4);

        table_next(world->robots, robot, &robot);
    }
}