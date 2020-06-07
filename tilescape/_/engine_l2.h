#pragma once
#include "../world_def.h"
#include "../place.h"
#include "engine_l1.h"


void ts_engine_l2_push_robot_x(ts_World *world,
                               ts_Robot *robot,
                               uint8_t distance)
{
    ts_Blob *blob_1;
    ts_Blob *blob_2;
    ts_Tile *tile_1;
    ts_Tile *tile_2;

    ts_Place place_x = robot->place_x;
    ts_Place place_y = robot->place_y;

    *ts_place_totl(&place_x) += distance;
    *ts_place_totl(&place_x) += (uint8_t)~0;
    uint16_t blob_x_1 = *ts_place_blob(&place_x);
    uint16_t blob_y_1 = *ts_place_blob(&place_y);

    *ts_place_totl(&place_y) += (uint8_t)~0;
    uint16_t blob_x_2 = *ts_place_blob(&place_x);
    uint16_t blob_y_2 = *ts_place_blob(&place_y);

    index2d_get(world->blobs, blob_x_1, blob_y_1, &blob_1);
    index2d_get(world->blobs, blob_x_2, blob_y_2, &blob_2);
    if (blob_1 && blob_2) {
        /* Q: Why not do blob 1 and blob 2 separately?
         *
         * A: Because it looks prettier this way. */

        tile_2 = &blob_2->tiles[*ts_place_tile(&place_x)]
                               [*ts_place_tile(&place_y)];
        *ts_place_totl(&place_y) -= (uint8_t)~0;
        tile_1 = &blob_1->tiles[*ts_place_tile(&place_x)]
                               [*ts_place_tile(&place_y)];
        *ts_place_totl(&place_x) -= (uint8_t)~0;
        *ts_place_mini(&place_x) = 0;

        if (!tile_1->type && !tile_2->type)
            ts_engine_l1_move_robot_x(robot, distance);
        else
            ts_engine_l1_teleport_robot(robot, place_x, robot->place_y);
    }
}

void ts_engine_l2_push_robot_y(ts_World *world,
                               ts_Robot *robot,
                               uint8_t distance)
{
    ts_Blob *blob_1;
    ts_Blob *blob_2;
    ts_Tile *tile_1;
    ts_Tile *tile_2;

    ts_Place place_x = robot->place_x;
    ts_Place place_y = robot->place_y;

    *ts_place_totl(&place_y) += distance;
    *ts_place_totl(&place_y) += (uint8_t)~0;
    uint16_t blob_x_1 = *ts_place_blob(&place_x);
    uint16_t blob_y_1 = *ts_place_blob(&place_y);

    *ts_place_totl(&place_x) += (uint8_t)~0;
    uint16_t blob_x_2 = *ts_place_blob(&place_x);
    uint16_t blob_y_2 = *ts_place_blob(&place_y);

    index2d_get(world->blobs, blob_x_1, blob_y_1, &blob_1);
    index2d_get(world->blobs, blob_x_2, blob_y_2, &blob_2);
    if (blob_1 && blob_2) {
        tile_2 = &blob_2->tiles[*ts_place_tile(&place_x)]
                               [*ts_place_tile(&place_y)];
        *ts_place_totl(&place_y) -= (uint8_t)~0;
        tile_1 = &blob_1->tiles[*ts_place_tile(&place_x)]
                               [*ts_place_tile(&place_y)];
        *ts_place_mini(&place_y) = 0;

        if (!tile_1->type && !tile_2->type)
            ts_engine_l1_move_robot_y(robot, distance);
        else
            ts_engine_l1_teleport_robot(robot, robot->place_x, place_y);
    }
}