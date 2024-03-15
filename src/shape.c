/*
** EPITECH PROJECT, 2024
** MY PAINT
** File description:
** none
*/

#include <stdlib.h>
#include <SFML/Graphics.h>
#include "header.h"

static sfVector2f get_shapeselector_pos(int tool_nb)
{
    float x = (float)(SHAPE_SELECTOR_X +
        (TOOL_MARGIN + SHAPE_SELECTOR_SIZE) * tool_nb);
    float y = (float)(TOP_BAR_HEIGHT +
        TOOL_BAR_POURCENTAGE * WIN_HEIGHT / 2 - TOOL_SELECTOR_SIZE / 2);

    return (sfVector2f){x, y};
}

static options_t *add_tool_selector(toolbar_t *toolbar, char const *text,
    enum init_mode mode, int rank_nb)
{
    options_t *shape = malloc(sizeof(options_t));
    sfVector2f pos = get_shapeselector_pos(rank_nb);
    sfVector2f size = {SHAPE_SELECTOR_SIZE, SHAPE_SELECTOR_SIZE};

    shape->button = init_button(pos, size);
    shape->next = toolbar->shape_list;
    if (mode == Text)
        set_rect_text(shape->button, shape->button->rect, text, FONT_SIZE);
    else if (mode == Image)
        set_rect_img(shape->button, text);
    sfRectangleShape_setFillColor(shape->button->rect, sfWhite);
    sfRectangleShape_setOutlineColor(shape->button->rect, sfBlack);
    sfRectangleShape_setOutlineThickness
        (shape->button->rect, SHAPE_SELECTOR_OT);
    toolbar->shape_list = shape;
    return toolbar->shape_list;
}

void init_shape_selector(toolbar_t *toolbar)
{
    toolbar->shape_list = NULL;
    add_tool_selector(toolbar, SQUARE_PNG_PATH, Image, 0);
    add_tool_selector(toolbar, CIRCLE_PNG_PATH, Image, 1);
}
