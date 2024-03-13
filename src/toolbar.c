/*
** EPITECH PROJECT, 2024
** MY PAINT
** File description:
** Toolbar functions
*/

#include <stdlib.h>
#include <SFML/Graphics.h>
#include "header.h"

static sfVector2f get_toolselector_pos(int tool_nb)
{
    float x = (float)(TOOL_SELECTOR_X +
        (TOOL_MARGIN + TOOL_SELECTOR_SIZE) * tool_nb);
    float y = (float)(TOP_BAR_HEIGHT +
        TOOL_BAR_POURCENTAGE * WIN_HEIGHT / 2 - TOOL_SELECTOR_SIZE / 2);

    return (sfVector2f){x, y};
}

static options_t *add_tool_selector(toolbar_t *toolbar, char const *text,
    enum init_mode mode, int rank_nb)
{
    options_t *tool = malloc(sizeof(options_t));
    sfVector2f pos = get_toolselector_pos(rank_nb);
    sfVector2f size = {TOOL_SELECTOR_SIZE, TOOL_SELECTOR_SIZE};

    tool->option = init_button(pos, size);
    tool->next = toolbar->tool_list;
    if (mode == Text)
        set_rect_text(tool->option, tool->option->rect, text, FONT_SIZE);
    else if (mode == Image)
        set_rect_img(tool->option, text);
    sfRectangleShape_setOutlineColor(tool->option->rect, sfBlack);
    sfRectangleShape_setOutlineThickness(tool->option->rect, TOOL_SELECT_OT);
    toolbar->tool_list = tool;
    return toolbar->tool_list;
}

static sfUint8 *init_tool_bar_pixels(void)
{
    return malloc((sizeof(sfUint8) * 4) *
        (WIN_WIDTH * WIN_HEIGHT * TOOL_BAR_POURCENTAGE + 1));
}

static void change_image_color(sfImage *image)
{
    for (unsigned int x = 0; x < WIN_WIDTH; x++) {
        for (unsigned int y = 0; y < WIN_HEIGHT * TOOL_BAR_POURCENTAGE; y++) {
            sfImage_setPixel(image, x, y, sfColor_fromRGB(232, 213, 211));
        }
    }
}

toolbar_t *init_toolbar(void)
{
    toolbar_t *toolbar = malloc(sizeof(toolbar_t));
    sfUint8 *pixel_array = init_tool_bar_pixels();

    toolbar->sprite = sfSprite_create();
    if (toolbar == NULL || pixel_array == NULL || toolbar->sprite == NULL)
        return NULL;
    toolbar->image = sfImage_createFromPixels
        (WIN_WIDTH, WIN_HEIGHT * TOOL_BAR_POURCENTAGE, pixel_array);
    change_image_color(toolbar->image);
    toolbar->texture = sfTexture_createFromImage(toolbar->image, NULL);
    toolbar->tool_list = NULL;
    add_tool_selector(toolbar, PENCIL_PNG_PATH, Image, 0);
    add_tool_selector(toolbar, ERASER_PNG_PATH, Image, 1);
    sfSprite_setTexture(toolbar->sprite, toolbar->texture, sfFalse);
    sfSprite_setPosition(toolbar->sprite, (sfVector2f){0, TOP_BAR_HEIGHT});
    return toolbar;
}
