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

static void draw_rect(w_data_t *wdata)
{
    sfVector2i mousePos = mouse_to_array_pos(wdata);
    sfColor color = wdata->w_content->draw->color;
    int size = wdata->w_content->draw->size;

    if (wdata->w_content->draw->draw_mode == Erase)
        color = sfWhite;
    for (int x = 0; x < wdata->w_content->draw->size &&
        mousePos.x + x < DRAW_WIDTH; x++) {
        sfImage_setPixel
            (wdata->w_content->image, mousePos.x + x, mousePos.y, color);
        for (int y = 0; y < size &&
            mousePos.y + y < DRAW_HEIGHT; y++)
            sfImage_setPixel
                (wdata->w_content->image,
                    mousePos.x + x, mousePos.y + y, color);
    }
}

static void check_error(int *error, int *x, int y)
{
    if (*error < 0)
            *error += 2 * y + 1;
        else {
            *x -= 1;
            *error += 2 * (y - *x + 1);
        }
}

static void draw_circle(w_data_t *w_data, int size)
{
    sfVector2i pos = mouse_to_array_pos(w_data);
    sfColor color = w_data->w_content->draw->color;
    int x = size;
    int y = 0;
    int error = 1 - x;

    if (w_data->w_content->draw->draw_mode == Erase)
        color = sfWhite;
    while (x >= y) {
        for (int i = pos.x - x; i <= pos.x + x; i++) {
            sfImage_setPixel(w_data->w_content->image, i, pos.y + y, color);
            sfImage_setPixel(w_data->w_content->image, i, pos.y - y, color);
        }
        for (int i = pos.x - y; i <= pos.x + y; i++) {
            sfImage_setPixel(w_data->w_content->image, i, pos.y + x, color);
            sfImage_setPixel(w_data->w_content->image, i, pos.y - x, color);
        }
        y++;
        check_error(&error, &x, y);
    }
}

void draw_or_not(w_data_t *w_data)
{
    if (mouse_in_draw_area(w_data) && sfMouse_isButtonPressed(sfMouseLeft)) {
        if (w_data->w_content->draw->shape == Square)
            draw_rect(w_data);
        else
            draw_circle(w_data, w_data->w_content->draw->size);
        sfTexture_updateFromImage
            (w_data->w_content->texture, w_data->w_content->image, 0, 0);
    }
}
