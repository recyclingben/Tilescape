#pragma once
#include "../world_def.h"
#include "math.h"
#include "engine_l1.h"
#include "engine_l2.h"

#define JUMP_STRENGTH       53 /* 0-127 */
#define JUMP_SHORT_STRENGTH 15 /* < JUMP_STRENGTH */


static inline void ts_engine_l3_step(ts_World *world)
{
    ts_Robot *robot;

    table_head(world->robots, &robot);
    while (robot) {
        ts_engine_l2_PushFlags flags_x = ts_engine_l2_push_robot_x(world, robot, robot->velocity_x);
        ts_engine_l2_PushFlags flags_y = ts_engine_l2_push_robot_y(world, robot, robot->velocity_y);

        if (flags_y & ts_engine_l2_PushFlags_FLOOR)
            robot->velocity_y = 0;
        if (flags_x & ts_engine_l2_PushFlags_LHIT
            || flags_x & ts_engine_l2_PushFlags_RHIT)
            robot->velocity_x = 0;

        robot->velocity_y += 1;
        if (robot->controller.push_n) robot->velocity_y -= 8;
        if (robot->controller.push_s) robot->velocity_y += 8;
        if (robot->controller.push_e) robot->velocity_x += 8;
        if (robot->controller.push_w) robot->velocity_x -= 8;

        robot->velocity_x -= robot->velocity_x / 4;
        robot->velocity_y -= robot->velocity_y / 32;

        if (abs(robot->velocity_x) < 4)
            robot->velocity_x = 0;

        if (robot->controller.jump)
            robot->velocity_y = -JUMP_STRENGTH;
        else if (robot->controller.jump_finish
             &&  robot->velocity_y < 0)
            /* Smaller jump. */
            robot->velocity_y = umax8(robot->velocity_y, -JUMP_SHORT_STRENGTH);

        robot->controller.jump        = false;
        robot->controller.jump_finish = false;

        table_next(world->robots, robot, &robot);
    }

    ++world->tick;
}