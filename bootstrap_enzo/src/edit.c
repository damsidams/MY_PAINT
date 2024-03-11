/*
** EPITECH PROJECT, 2024
** MY PAINT
** File description:
** none
*/

#include <SFML/Graphics.h>
#include "header.h"

sfBool set_rect_text(b_content_t *button, sfRectangleShape *rect,
    char const *text, unsigned int font_size)
{
    sfFont *font = sfFont_createFromFile(FONTPATH);
    sfFloatRect bounds = sfRectangleShape_getGlobalBounds(rect);
    sfFloatRect txt_bounds;

    if (font == NULL) {
        my_putstr_err("Error: font not found.\n");
        return sfFalse;
    }
    if (rect == NULL)
        return sfFalse;
    button->txt = sfText_create();
    sfText_setFont(button->txt, font);
    sfText_setString(button->txt, text);
    sfText_setColor(button->txt, sfBlack);
    sfText_setCharacterSize(button->txt, font_size);
    txt_bounds = sfText_getGlobalBounds(button->txt);
    sfText_setPosition(button->txt, (sfVector2f) {bounds.left +
        bounds.width / 2 - txt_bounds.width / 2, bounds.top + bounds.height
        / 2 - txt_bounds.height / 2});
    return sfTrue;
}

sfBool set_rect_img(b_content_t *button, char const *img_path)
{
    sfTexture *texture = sfTexture_createFromFile(img_path, NULL);

    sfSprite_setTexture(button->sprite, texture, sfFalse);
    sfRectangleShape_setTexture(button->rect, texture, NULL);
    sfTexture_destroy(texture);
}
