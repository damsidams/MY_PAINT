/*
** EPITECH PROJECT, 2024
** MY PAINT
** File description:
** Functions related to colors
*/

#include <SFML/Graphics.h>
#include <SFML/Config.h>
#include <stdlib.h>
#include "header.h"

void draw_zone(sfImage *image, sfColor color)
{
    sfVector2i start = {0, 0};

    for (int x = 0; x < DRAW_WIDTH - start.x; x++) {
        sfImage_setPixel(image, start.x + x, start.y, color);
        for (int y = 0; y < DRAW_HEIGHT - start.y; y++)
            sfImage_setPixel(image, start.x + x, start.y + y, color);
    }
}

int mouse_in_draw_area(w_data_t *wdata)
{
    sfVector2i mousePos = sfMouse_getPositionRenderWindow(wdata->win);
    sfVector2i notDrawingArea = {WIN_WIDTH, TOP_BAR_HEIGHT + TOOL_BAR_HEIGHT};

    if (mousePos.y > notDrawingArea.y)
        return 1;
    return 0;
}

static sfVector2i mouse_to_array_pos(w_data_t *wdata)
{
    sfVector2i mousePos = sfMouse_getPositionRenderWindow(wdata->win);
    sfVector2i mousePosInArraw =
        {mousePos.x, mousePos.y - (TOOL_BAR_HEIGHT + TOP_BAR_HEIGHT)};

    return mousePosInArraw;
}

void draw_rect(int size, sfColor color, w_data_t *wdata)
{
    sfVector2i mousePos = mouse_to_array_pos(wdata);

    for (int x = 0; x < size && mousePos.x + x < DRAW_WIDTH; x++) {
        sfImage_setPixel
            (wdata->w_content->image, mousePos.x + x, mousePos.y, color);
        for (int y = 0; y < size && mousePos.y + y < DRAW_HEIGHT; y++)
            sfImage_setPixel
                (wdata->w_content->image,
                    mousePos.x + x, mousePos.y + y, color);
    }
}

void draw_or_not(sfEvent *event, w_data_t *w_data)
{
    if (mouse_in_draw_area(w_data) && event->type == sfEvtMouseButtonPressed) {
        draw_rect(15, sfBlack, w_data);
        sfTexture_updateFromImage
            (w_data->w_content->texture, w_data->w_content->image, 0, 0);
    }
}
