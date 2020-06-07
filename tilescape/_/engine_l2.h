#pragma once
#include "../world_def.h"
#include "../place.h"
#include "engine_l1.h"


/* Yikes! */
bool ts_engine_l2_can_push_x(ts_World *world,
                             ts_Robot *robot,
                             int8_t distance)
{
    /* This looks like a lot but it's really just a lot of boilerplate.
     * We take the four tiles we could possibly bump into on an X coordinate change,
     * and check if we ever collide after applying the movement. */
    ts_Blob *blob_1;
    ts_Blob *blob_2;
    ts_Blob *blob_3;
    ts_Blob *blob_4;
    ts_Tile *tile_1;
    ts_Tile *tile_2;
    ts_Tile *tile_3;
    ts_Tile *tile_4;

    ts_Place place_x = robot->place_x;
    ts_Place place_y = robot->place_y;

    *ts_place_totl(&place_x) += distance;
    uint16_t blob_x_0 = *ts_place_blob(&place_x);
    uint16_t blob_y_0 = *ts_place_blob(&place_y);

    *ts_place_totl(&place_y) -= (uint8_t)~0;
    uint16_t blob_x_n = *ts_place_blob(&place_x);
    uint16_t blob_y_n = *ts_place_blob(&place_y);

    *ts_place_totl(&place_y) += (uint8_t)~0;
    *ts_place_totl(&place_x) += (uint8_t)~0;
    uint16_t blob_x_1 = *ts_place_blob(&place_x);
    uint16_t blob_y_1 = *ts_place_blob(&place_y);

    *ts_place_totl(&place_y) += (uint8_t)~0;
    uint16_t blob_x_2 = *ts_place_blob(&place_x);
    uint16_t blob_y_2 = *ts_place_blob(&place_y);

    index2d_get(world->blobs, blob_x_0, blob_y_0, &blob_1);
    index2d_get(world->blobs, blob_x_1, blob_y_1, &blob_3);
    index2d_get(world->blobs, blob_x_2, blob_y_2, &blob_4);
    index2d_get(world->blobs, blob_x_2, blob_y_2, &blob_2);

    if (blob_1 && blob_2 && blob_3 && blob_4) {
        tile_4 = &blob_4->tiles[*ts_place_tile(&place_x)]
                               [*ts_place_tile(&place_y)];
        *ts_place_totl(&place_y) -= (uint8_t)~0;
        tile_3 = &blob_3->tiles[*ts_place_tile(&place_x)]
                               [*ts_place_tile(&place_y)];
        *ts_place_totl(&place_x) -= (uint8_t)~0;
        tile_2 = &blob_2->tiles[*ts_place_tile(&place_x)]
                               [*ts_place_tile(&place_y)];
        *ts_place_totl(&place_y) += (uint8_t)~0;
        tile_1 = &blob_1->tiles[*ts_place_tile(&place_x)]
                               [*ts_place_tile(&place_y)];

        return !tile_1->type &&
               !tile_2->type &&
               !tile_3->type &&
               !tile_4->type;
    }
    return false;
}

bool ts_engine_l2_can_push_y(ts_World *world,
                             ts_Robot *robot,
                             int8_t distance)
{
    ts_Blob *blob_1;
    ts_Blob *blob_2;
    ts_Blob *blob_3;
    ts_Blob *blob_4;
    ts_Tile *tile_1;
    ts_Tile *tile_2;
    ts_Tile *tile_3;
    ts_Tile *tile_4;

    ts_Place place_x = robot->place_x;
    ts_Place place_y = robot->place_y;

    *ts_place_totl(&place_y) += distance;
    uint16_t blob_x_0 = *ts_place_blob(&place_x);
    uint16_t blob_y_0 = *ts_place_blob(&place_y);

    *ts_place_totl(&place_x) -= (uint8_t)~0;
    uint16_t blob_x_n = *ts_place_blob(&place_x);
    uint16_t blob_y_n = *ts_place_blob(&place_y);

    *ts_place_totl(&place_x) += (uint8_t)~0;
    *ts_place_totl(&place_y) += (uint8_t)~0;
    uint16_t blob_x_1 = *ts_place_blob(&place_x);
    uint16_t blob_y_1 = *ts_place_blob(&place_y);

    *ts_place_totl(&place_x) += (uint8_t)~0;
    uint16_t blob_x_2 = *ts_place_blob(&place_x);
    uint16_t blob_y_2 = *ts_place_blob(&place_y);

    index2d_get(world->blobs, blob_x_0, blob_y_0, &blob_1);
    index2d_get(world->blobs, blob_x_1, blob_y_1, &blob_3);
    index2d_get(world->blobs, blob_x_2, blob_y_2, &blob_4);
    index2d_get(world->blobs, blob_x_2, blob_y_2, &blob_2);

    if (blob_1 && blob_2 && blob_3 && blob_4) {
        tile_4 = &blob_4->tiles[*ts_place_tile(&place_x)]
                               [*ts_place_tile(&place_y)];
        *ts_place_totl(&place_x) -= (uint8_t)~0;
        tile_3 = &blob_3->tiles[*ts_place_tile(&place_x)]
                               [*ts_place_tile(&place_y)];
        *ts_place_totl(&place_y) -= (uint8_t)~0;
        tile_2 = &blob_2->tiles[*ts_place_tile(&place_x)]
                               [*ts_place_tile(&place_y)];
        *ts_place_totl(&place_x) += (uint8_t)~0;
        tile_1 = &blob_1->tiles[*ts_place_tile(&place_x)]
                               [*ts_place_tile(&place_y)];

        return !tile_1->type &&
               !tile_2->type &&
               !tile_3->type &&
               !tile_4->type;
    }
    return false;
}

void ts_engine_l2_push_robot_x(ts_World *world,
                               ts_Robot *robot,
                               int8_t distance)
{

    if (ts_engine_l2_can_push_x(world, robot, distance))
        /* Get as close as we can. */
        *ts_place_totl(&robot->place_x) += distance;
    else
        *ts_place_mini(&robot->place_x) = 0;
}

void ts_engine_l2_push_robot_y(ts_World *world,
                               ts_Robot *robot,
                               int8_t distance)
{
    *ts_place_totl(&robot->place_y) += distance;

    if (!ts_engine_l2_can_push_y(world, robot, 0)) {
        *ts_place_totl(&robot->place_y) -= distance;
        *ts_place_mini(&robot->place_y) = 0;
    }
}