/*
** EPITECH PROJECT, 2024
** MY PAINT
** File description:
** Functions related to the color picker
*/

#include <stdlib.h>
#include <SFML/Graphics.h>
#include "header.h"

static int my_circ_contains(sfCircleShape *circle, sfVector2f pos)
{
    float size = sfCircleShape_getRadius(circle);
    sfVector2f circ_pos = sfCircleShape_getPosition(circle);

    if (pos.x < circ_pos.x || pos.y < circ_pos.y)
        return 0;
    circ_pos.x += size;
    circ_pos.y += size;
    if ((pos.x - circ_pos.x) * (pos.x - circ_pos.x) +
        (pos.y - circ_pos.y) * (pos.y - circ_pos.y) > size * size)
        return 0;
    return 1;
}

static void pick_color(win_content_t *wc, picker_t *picker, sfVector2f pos)
{
    sfVector2i image_pos = {pos.x - COLOR_PICKER_X, pos.y - (TOP_BAR_HEIGHT +
        (TOOL_BAR_HEIGHT / 2 - COLOR_PICKER_RADIUS))};

    wc->draw->color = sfImage_getPixel(picker->image, image_pos.x, image_pos.y);
}

void color_pick_event(win_content_t *wc, toolbar_t *toolbar, sfEvent *event)
{
    sfMouseButtonEvent evt_pressed = event->mouseButton;

    if (event->type == sfEvtMouseButtonPressed) {
        if (my_circ_contains(toolbar->color_picker->circle,
            (sfVector2f){evt_pressed.x, evt_pressed.y}))
            pick_color(wc, toolbar->color_picker,
                (sfVector2f){evt_pressed.x, evt_pressed.y});
    }
}

void init_color_picker(toolbar_t *toolbar)
{
    picker_t *picker = malloc(sizeof(picker_t));

    picker->circle = sfCircleShape_create();
    sfCircleShape_setRadius(picker->circle, COLOR_PICKER_RADIUS);
    sfCircleShape_setPosition(picker->circle, (sfVector2f){COLOR_PICKER_X, TOP_BAR_HEIGHT +
            (TOOL_BAR_HEIGHT / 2 - COLOR_PICKER_RADIUS)});
    picker->image = sfImage_createFromFile(COLOR_PICKER_PNG_PATH);
    picker->texture = sfTexture_createFromImage(picker->image, NULL);
    sfCircleShape_setTexture(picker->circle, picker->texture, sfFalse);
    toolbar->color_picker = picker;
}
