#pragma once
#include "../world_def.h"
#include "../place.h"
#include "engine_l1.h"

#define TSROBOT_W 220
#define TSROBOT_H 255

#define ts_engine_l2_PushFlags uint8_t
#define ts_engine_l2_PushFlags_FLOOR (1 << 0)
#define ts_engine_l2_PushFlags_CEIL  (1 << 1)
#define ts_engine_l2_PushFlags_LHIT  (1 << 2)
#define ts_engine_l2_PushFlags_RHIT  (1 << 3)


/* Yikes! */
static inline bool ts_engine_l2_can_push_x(TSWorld *world,
                                           TSRobot *robot,
                                           int8_t distance)
{
    /* Test if, after translation, four corners of robot are not in contact with a tile. */
    TSBlob *blob_0;
    TSBlob *blob_1;
    TSBlob *blob_2;
    TSBlob *blob_3;

    TSTile *tile_0;
    TSTile *tile_1;
    TSTile *tile_2;
    TSTile *tile_3;


    TSPlace place_x = robot->place_x;
    TSPlace place_y = robot->place_y;


    *ts_place_totl(&place_x) += distance;
    uint16_t blob_x_0 = *ts_place_blob(&place_x);
    uint16_t blob_y_0 = *ts_place_blob(&place_y);

    *ts_place_totl(&place_y) += TSROBOT_H;
    uint16_t blob_x_1 = *ts_place_blob(&place_x);
    uint16_t blob_y_1 = *ts_place_blob(&place_y);

    *ts_place_totl(&place_x) += TSROBOT_W;
    uint16_t blob_x_2 = *ts_place_blob(&place_x);
    uint16_t blob_y_2 = *ts_place_blob(&place_y);

    *ts_place_totl(&place_y) -= TSROBOT_H;
    uint16_t blob_x_3 = *ts_place_blob(&place_x);
    uint16_t blob_y_3 = *ts_place_blob(&place_y);


    index2d_get(world->blobs, blob_x_0, blob_y_0, &blob_0);
    index2d_get(world->blobs, blob_x_1, blob_y_1, &blob_1);
    index2d_get(world->blobs, blob_x_2, blob_y_2, &blob_2);
    index2d_get(world->blobs, blob_x_3, blob_y_3, &blob_3);


    if (blob_0 && blob_1 && blob_2 && blob_3) {
        place_x = robot->place_x;
        place_y = robot->place_y;


        *ts_place_totl(&place_x) += distance;
        tile_0 = &blob_0->tiles[*ts_place_tile(&place_x)][*ts_place_tile(&place_y)];

        *ts_place_totl(&place_y) += TSROBOT_H;
        tile_1 = &blob_1->tiles[*ts_place_tile(&place_x)][*ts_place_tile(&place_y)];

        *ts_place_totl(&place_x) += TSROBOT_W;
        tile_2 = &blob_2->tiles[*ts_place_tile(&place_x)][*ts_place_tile(&place_y)];

        *ts_place_totl(&place_y) -= TSROBOT_H;
        tile_3 = &blob_3->tiles[*ts_place_tile(&place_x)][*ts_place_tile(&place_y)];


        return !tile_0->type &&
               !tile_1->type &&
               !tile_2->type &&
               !tile_3->type;
    }
    return false;
}

static inline bool ts_engine_l2_can_push_y(TSWorld *world,
                                           TSRobot *robot,
                                           int8_t distance)
{
    TSBlob *blob_0;
    TSBlob *blob_1;
    TSBlob *blob_2;
    TSBlob *blob_3;

    TSTile *tile_0;
    TSTile *tile_1;
    TSTile *tile_2;
    TSTile *tile_3;


    TSPlace place_x = robot->place_x;
    TSPlace place_y = robot->place_y;


    *ts_place_totl(&place_y) += distance;
    uint16_t blob_x_0 = *ts_place_blob(&place_x);
    uint16_t blob_y_0 = *ts_place_blob(&place_y);

    *ts_place_totl(&place_x) += TSROBOT_W;
    uint16_t blob_x_1 = *ts_place_blob(&place_x);
    uint16_t blob_y_1 = *ts_place_blob(&place_y);

    *ts_place_totl(&place_y) += TSROBOT_H;
    uint16_t blob_x_2 = *ts_place_blob(&place_x);
    uint16_t blob_y_2 = *ts_place_blob(&place_y);

    *ts_place_totl(&place_x) -= TSROBOT_W;
    uint16_t blob_x_3 = *ts_place_blob(&place_x);
    uint16_t blob_y_3 = *ts_place_blob(&place_y);


    index2d_get(world->blobs, blob_x_0, blob_y_0, &blob_0);
    index2d_get(world->blobs, blob_x_1, blob_y_1, &blob_1);
    index2d_get(world->blobs, blob_x_2, blob_y_2, &blob_2);
    index2d_get(world->blobs, blob_x_3, blob_y_3, &blob_3);


    if (blob_0 && blob_1 && blob_2 && blob_3) {
        TSPlace place_x = robot->place_x;
        TSPlace place_y = robot->place_y;


        *ts_place_totl(&place_y) += distance;
        tile_0 = &blob_0->tiles[*ts_place_tile(&place_x)][*ts_place_tile(&place_y)];

        *ts_place_totl(&place_x) += TSROBOT_W;
        tile_1 = &blob_1->tiles[*ts_place_tile(&place_x)][*ts_place_tile(&place_y)];

        *ts_place_totl(&place_y) += TSROBOT_H;
        tile_2 = &blob_2->tiles[*ts_place_tile(&place_x)][*ts_place_tile(&place_y)];

        *ts_place_totl(&place_x) -= TSROBOT_W;
        tile_3 = &blob_3->tiles[*ts_place_tile(&place_x)][*ts_place_tile(&place_y)];


        return !tile_0->type &&
               !tile_1->type &&
               !tile_2->type &&
               !tile_3->type;
    }
    return false;
}

static inline ts_engine_l2_PushFlags ts_engine_l2_push_robot_x(TSWorld *world,
                                                               TSRobot *robot,
                                                               int8_t distance)
{
    *ts_place_totl(&robot->place_x) += distance;

    if (!ts_engine_l2_can_push_x(world, robot, 0)) {
        if (distance > 0) {
            /* Get as close as we can. */
            *ts_place_mini(&robot->place_x) = 0;
            *ts_place_totl(&robot->place_x) += (uint8_t)~0 - TSROBOT_W;
            return ts_engine_l2_PushFlags_RHIT;
        } else {
            *ts_place_totl(&robot->place_x) -= distance;
            *ts_place_mini(&robot->place_x) = 0;
            return ts_engine_l2_PushFlags_LHIT;
        }
    }

    return 0;
}

static inline ts_engine_l2_PushFlags ts_engine_l2_push_robot_y(TSWorld *world,
                                                               TSRobot *robot,
                                                               int8_t distance)
{
    *ts_place_totl(&robot->place_y) += distance;

    if (!ts_engine_l2_can_push_y(world, robot, 0)) {
        if (distance > 0) {
            *ts_place_mini(&robot->place_y) = 0;
            *ts_place_totl(&robot->place_y) += (uint8_t)~0 - TSROBOT_H;
            return ts_engine_l2_PushFlags_FLOOR;
        } else {
            *ts_place_totl(&robot->place_y) -= distance;
            *ts_place_mini(&robot->place_y) = 0;
            return ts_engine_l2_PushFlags_CEIL;
        }
    }

    return 0;
}