#include <stdio.h>
#include <unistd.h>
#include <SFML/Graphics.h>
#include "tilescape/place.h"
#include "tilescape/world.h"
#include "tilescape/robot.h"
#include "tilescape/blob.h"
#include "tilescape/plugins/pack.h"


int main()
{
    World *world;
    Robot *robot;
    Controller *controller;
    Blob *blob;
    Tile *tile;

    ts_world_make(&world);

    ts_world_add_robot(world, rand(), &robot);
    ts_robot_get_controller(robot, &controller);

    robot->place_x.int_32 = 5 * ((uint8_t)~0 + 1);
    robot->place_y.int_32 = 7 * ((uint8_t)~0 + 1);

    Place place_y = ts_robot_get_place_y(robot);
    Place place_x = ts_robot_get_place_x(robot);
    ts_world_add_blob(world, place_x, place_y, &blob);

    ts_blob_get_tile(blob, 4, 6, &tile); tile->type = 1;
    ts_blob_get_tile(blob, 5, 4, &tile); tile->type = 1;
    ts_blob_get_tile(blob, 7, 4, &tile); tile->type = 1;

    /* Display */

    sfVideoMode mode       = { 800, 600, 32 };
    sfRenderWindow* window = sfRenderWindow_create(mode, "SFML window", sfResize | sfClose, NULL);
    sfEvent event;

    sfWindow_setKeyRepeatEnabled((sfWindow *)window, false);
    while (sfRenderWindow_isOpen(window)) {
        usleep(8000);
        while (sfRenderWindow_pollEvent(window, &event)) {
            if (event.type == sfEvtClosed)
                sfRenderWindow_close(window);
            else if (event.type == sfEvtKeyPressed)
                switch (event.key.code) {
                    case 22:
                        controller->jump = true;
                        break;
                    case 18:
                        controller->push_s = true;
                        break;
                    case 3:
                        controller->push_e = true;
                        break;
                    case 0:
                        controller->push_w = true;
                        break;
                }
            else if (event.type == sfEvtKeyReleased)
                switch (event.key.code) {
                    case 22:
                        controller->jump_finish = true;
                        break;
                    case 18:
                        controller->push_s = false;
                        break;
                    case 3:
                        controller->push_e = false;
                        break;
                    case 0:
                        controller->push_w = false;
                        break;
                }
        }


        ts_world_get_robots_head(world, &robot);
        while (robot) {
            /* + 1 because rounding might be off. Better too large than too small. */
            int robot_vis_h = 16 * ROBOT_H / 255 + 1;
            int robot_vis_w = 16 * ROBOT_W / 255 + 1;

            place_x = ts_robot_get_place_x(robot);
            place_y = ts_robot_get_place_y(robot);
            ts_world_add_blob(world, place_x, place_y, &blob);

            for (int x = 0; x <= (uint8_t)~0; ++x)
            for (int y = 0; y <= (uint8_t)~0; ++y) {
                Tile *tile;
                ts_blob_get_tile(blob, x, y, &tile);

                if (tile->type) {
                    sfRectangleShape *rect = sfRectangleShape_create();
                    sfRectangleShape_setPosition(rect, (sfVector2f) {*ts_place_blob(&place_x) * 16 * 16 + x * 16,
                                                                     *ts_place_blob(&place_y) * 16 * 16 + y * 16});
                    sfRectangleShape_setSize(rect, (sfVector2f) { 16, 16 });
                    sfRenderWindow_drawShape(window, (sfShape *) rect, NULL);
                }
            }

            sfRectangleShape *rect = sfRectangleShape_create();
            sfRectangleShape_setPosition(rect, (sfVector2f) {*ts_place_totl(&place_x) / 16,
                                                             *ts_place_totl(&place_y) / 16});
            sfRectangleShape_setSize(rect, (sfVector2f) {robot_vis_w, robot_vis_h});
            sfRenderWindow_drawShape(window, (sfShape *) rect, NULL);

            ts_world_get_robots_next(world, robot, &robot);
        }
        ts_world_step(world);

        sfRenderWindow_display(window);
        sfRenderWindow_clear(window, sfBlack);
    }
    sfRenderWindow_destroy(window);
}