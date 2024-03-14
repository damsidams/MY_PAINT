/*
** EPITECH PROJECT, 2024
** MY PAINT
** File description:
** Functions related to the color picker
*/

#include <stdlib.h>
#include <stdbool.h>
#include <SFML/Graphics.h>
#include "header.h"

static int my_rect_contains(sfRectangleShape *rect, sfVector2f pos)
{
    sfVector2f size = sfRectangleShape_getSize(rect);
    sfVector2f rect_pos = sfRectangleShape_getPosition(rect);

    if (pos.x < rect_pos.x || pos.y < rect_pos.y)
        return false;
    rect_pos.x += size.x;
    rect_pos.y += size.y;
    if (pos.x > rect_pos.x || pos.y > rect_pos.y)
        return false;
    return true;
}

static void pick_color(win_content_t *wc, picker_t *picker, sfVector2f pos)
{
    sfVector2f rect_pos = sfRectangleShape_getPosition(picker->rect);
    sfVector2f image_size = sfRectangleShape_getSize(picker->rect);
    sfVector2f image_pos;

    image_pos.x = (pos.x - rect_pos.x) / image_size.x * CP_IMAGE_WIDTH;
    image_pos.y = (pos.y - rect_pos.y) / image_size.y * CP_IMAGE_HEIGHT;
    //printf("x: %f | y: %f\n", pos.x - image_pos.x, pos.y - image_pos.y);
    //printf("x pos: %f, size: %f\n", image_pos.x, COLOR_PICKER_WIDTH);
    wc->draw->color = sfImage_getPixel(picker->image, image_pos.x, image_pos.y);
}

void color_pick_event(win_content_t *wc, toolbar_t *toolbar, sfEvent *event)
{
    sfMouseButtonEvent evt_pressed = event->mouseButton;

    if (event->type == sfEvtMouseButtonPressed) {
        if (my_rect_contains(toolbar->color_picker->rect,
            (sfVector2f){evt_pressed.x, evt_pressed.y}))
            pick_color(wc, toolbar->color_picker,
                (sfVector2f){evt_pressed.x, evt_pressed.y});
    }
}

void init_color_picker(toolbar_t *toolbar)
{
    picker_t *picker = malloc(sizeof(picker_t));

    picker->rect = sfRectangleShape_create();
    sfRectangleShape_setSize(picker->rect, (sfVector2f){COLOR_PICKER_WIDTH, COLOR_PICKER_HEIGHT});
    sfRectangleShape_setPosition(picker->rect, (sfVector2f){COLOR_PICKER_X, TOP_BAR_HEIGHT +
            (TOOL_BAR_HEIGHT / 2 - COLOR_PICKER_HEIGHT/ 2)});
    picker->image = sfImage_createFromFile(COLOR_PICKER_PNG_PATH);
    picker->texture = sfTexture_createFromImage(picker->image, NULL);
    sfRectangleShape_setTexture(picker->rect, picker->texture, sfFalse);
    toolbar->color_picker = picker;
}
