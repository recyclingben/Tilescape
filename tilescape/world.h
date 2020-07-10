#pragma once
#include <string.h>
#include <biglist/list.h>

#include "world_def.h"
#include "robot.h"
#include "_/engine_l1.h"
#include "_/engine_l2.h"
#include "_/engine_l3.h"


/*
 * BOILERPLATE/RUN FUNCTIONS
 */

static inline void ts_world_make(ts_World **out_world)
{
    *out_world = malloc(sizeof(ts_World));
    (*out_world)->tick = 0;
    index2d_make(sizeof(ts_Blob), &(*out_world)->blobs);
    index_make(sizeof(ts_Robot *), &(*out_world)->robots);
    table_make(sizeof(ts_Robot), (uint16_t)~0, &(*out_world)->robots_table);
}

static inline void ts_world_step(ts_World *world)
{
    ts_engine_l3_step(world);
}

/*
 * GET/ADD FUNCTIONS
 */

static inline void ts_world_get_tick(ts_World *world,
                                     uint8_t *out_tick)
{
    *out_tick = world->tick;
}

static inline void ts_world_add_robot(ts_World *world,
                                      uint32_t key,
                                      ts_Robot **out_robot)
{
    ts_Robot **reference;
    index_get(world->robots, key, &reference);

    if (!reference) {
        table_add(world->robots_table, out_robot);
        index_add(world->robots, key, &reference);
        *reference = *out_robot;

        memset(*out_robot, 0, sizeof(ts_Robot));
        (*out_robot)->key = key;
    } else
        *out_robot = *reference;
}

static inline void ts_world_get_robots_head(ts_World *world,
                                            ts_Robot **out_robot)
{
    table_head(world->robots_table, out_robot);
}

static inline void ts_world_get_robots_next(ts_World *world,
                                            ts_Robot *robot,
                                            ts_Robot **out_robot)
{
    table_next(world->robots_table, robot, out_robot);
}

static inline void ts_world_add_blob(ts_World *world,
                                     ts_Place x,
                                     ts_Place y,
                                     ts_Blob **out_blob)
{
    index2d_get(world->blobs, *ts_place_blob(&x),
                              *ts_place_blob(&y), out_blob);
    if (!*out_blob) {
        index2d_add(world->blobs, *ts_place_blob(&x),
                                  *ts_place_blob(&y), out_blob);
        memset(*out_blob, 0, sizeof(ts_Blob));
    }
}