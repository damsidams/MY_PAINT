/*
** EPITECH PROJECT, 2024
** MY PAINT
** File description:
** Toolbar functions
*/

#include <stdlib.h>
#include <SFML/Graphics.h>
#include "header.h"

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

static sfVector2f get_toolselector_pos(int tool_nb)
{
    float x = (float)TOOL_SELECTOR_X + (TOOL_MARGIN + TOOL_SELECTOR_SIZE) * tool_nb;
    float y = (float)(TOP_BAR_HEIGHT +
        TOOL_BAR_POURCENTAGE * WIN_HEIGHT / 2 - TOOL_SELECTOR_SIZE / 2);

    return (sfVector2f){x, y};
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
    toolbar->button = init_button(get_toolselector_pos(0),
        (sfVector2f){TOOL_SELECTOR_SIZE, TOOL_SELECTOR_SIZE});
    set_rect_img(toolbar->button, PENCIL_PNG_PATH);
    sfRectangleShape_setOutlineColor(toolbar->button->rect, sfBlack);
    sfRectangleShape_setOutlineThickness(toolbar->button->rect, TOOL_SELECT_OT);
    sfSprite_setTexture(toolbar->sprite, toolbar->texture, sfFalse);
    sfSprite_setPosition(toolbar->sprite, (sfVector2f){0, TOP_BAR_HEIGHT});
    return toolbar;
}
