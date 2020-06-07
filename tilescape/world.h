#pragma once
#include <biglist/list.h>

#include "world_def.h"
#include "_/engine_l1.h"
#include "_/engine_l2.h"
#include "_/engine_l3.h"


/*
 * BOILERPLATE/RUN FUNCTIONS
 */

void ts_world_make(ts_World **out_world)
{
    *out_world = malloc(sizeof(ts_World));
    index2d_make(sizeof(ts_Blob), &(*out_world)->blobs);
    table_make(sizeof(ts_Robot), (uint16_t)~0, &(*out_world)->robots);
}

void ts_world_step(ts_World *world)
{
    ts_engine_l3_step(world);
}

/*
 * GET/ADD FUNCTIONS
 */

void ts_world_add_robot(ts_World *world,
                        ts_Robot **out_robot)
{
    table_add(world->robots, out_robot);
}

void ts_world_get_robots_head(ts_World *world,
                              ts_Robot **out_robot)
{
    table_head(world->robots, out_robot);
}

void ts_world_get_robots_next(ts_World *world,
                              ts_Robot *robot,
                              ts_Robot **out_robot)
{
    table_next(world->robots, robot, out_robot);
}

void ts_world_add_blob(ts_World *world,
                       uint16_t x,
                       uint16_t y,
                       ts_Blob **out_blob)
{
    index2d_get(world->blobs, x, y, out_blob);
    if (!*out_blob)
        index2d_add(world->blobs, x, y, out_blob);
}