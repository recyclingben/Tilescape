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

static inline void ts_world_make(TSWorld **out_world)
{
    *out_world = malloc(sizeof(TSWorld));
    (*out_world)->tick = 0;
    index2d_make(sizeof(TSBlob), &(*out_world)->blobs);
    index_make(sizeof(TSRobot *), &(*out_world)->robots);
    table_make(sizeof(TSRobot), (uint16_t)~0, &(*out_world)->robots_table);
}

static inline void ts_world_step(TSWorld *world)
{
    ts_engine_l3_step(world);
}

/*
 * GET/ADD FUNCTIONS
 */

static inline void ts_world_get_tick(TSWorld *world,
                                     uint8_t *out_tick)
{
    *out_tick = world->tick;
}

static inline void ts_world_add_robot(TSWorld *world,
                                      uint32_t key,
                                      TSRobot **out_robot)
{
    TSRobot **reference;
    index_get(world->robots, key, &reference);

    if (!reference) {
        table_add(world->robots_table, out_robot);
        index_add(world->robots, key, &reference);
        *reference = *out_robot;

        memset(*out_robot, 0, sizeof(TSRobot));
        (*out_robot)->key = key;
    } else
        *out_robot = *reference;
}

static inline void ts_world_remove_robot(TSWorld *world,
                                         uint32_t key)
{
    TSRobot **reference;
    index_get(world->robots, key, &reference);

    if (reference) {
        table_remove(world->robots_table, *reference);
        index_remove(world->robots, key);
    }
}

static inline void ts_world_get_robots_head(TSWorld *world,
                                            TSRobot **out_robot)
{
    table_head(world->robots_table, out_robot);
}

static inline void ts_world_get_robots_next(TSWorld *world,
                                            TSRobot *robot,
                                            TSRobot **out_robot)
{
    table_next(world->robots_table, robot, out_robot);
}

static inline void ts_world_robots_clear(TSWorld *world)
{
    table_clear(world->robots_table);
    index_slow_clear(world->robots);
}

static inline void ts_world_add_blob(TSWorld *world,
                                     TSPlace x,
                                     TSPlace y,
                                     TSBlob **out_blob)
{
    index2d_get(world->blobs, *ts_place_blob(&x),
                              *ts_place_blob(&y), out_blob);
    if (!*out_blob) {
        index2d_add(world->blobs, *ts_place_blob(&x),
                                  *ts_place_blob(&y), out_blob);
        memset(*out_blob, 0, sizeof(TSBlob));
    }
}