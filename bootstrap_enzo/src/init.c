/*
** EPITECH PROJECT, 2024
** MY PAINT
** File description:
** none
*/

#include <stdlib.h>
#include <SFML/Graphics.h>
#include "header.h"

sfBool check_click(b_content_t *button,
    sfMouseButtonEvent *event)
{
    sfFloatRect tmp_rect = sfRectangleShape_getGlobalBounds(button->rect);

    if (sfFloatRect_contains(&tmp_rect, event->x, event->y)) {
        button->state = PRESSED;
        return sfTrue;
    }
    if (button->state == PRESSED)
        button->state = RELEASED;
    return sfFalse;
}

sfBool is_hover(b_content_t *button, sfMouseMoveEvent *event)
{
    sfFloatRect tmp_rect = sfRectangleShape_getGlobalBounds(button->rect);

    if (sfFloatRect_contains(&tmp_rect, event->x, event->y) && button->state != PRESSED) {
        button->state = HOVER;
        return sfTrue;
    }
    if (button->state == HOVER)
        button->state = NONE;
    return sfFalse;
}

b_content_t *init_button(sfVector2f position, sfVector2f size)
{
    sfRectangleShape *rect = sfRectangleShape_create();
    b_content_t *button = malloc(sizeof(b_content_t));

    sfRectangleShape_setPosition(rect, position);
    sfRectangleShape_setSize(rect, size);
    sfRectangleShape_setFillColor(rect, sfWhite);
    button->rect = rect;
    button->is_clicked = &check_click;
    button->is_hover = &is_hover;
    button->txt = NULL;
    return button;
}

static win_content_t *init_win_content(void)
{
    win_content_t *wc = malloc(sizeof(win_content_t));
    sfUint8 *buffer = init_pixel_array();
    sfIntRect image_rect = {0, 0, WIN_WIDTH, WIN_HEIGHT};

    if (buffer == NULL || wc == NULL)
        return NULL;
    wc->menu = create_drop_menu((sfVector2f){0, 0}, (sfVector2f){TOP_BAR_WIDTH, TOP_BAR_HEIGHT});
    wc->image = sfImage_createFromPixels(WIN_WIDTH, WIN_HEIGHT, buffer);
    wc->sprite = sfSprite_create();
    wc->texture = sfTexture_createFromImage(wc->image, &image_rect);
    sfSprite_setTexture(wc->sprite, wc->texture, sfTrue);
    sfSprite_setTextureRect(wc->sprite, image_rect);
    wc->toolbar = init_toolbar();
    return wc;
}

w_data_t *init_win(void)
{
    w_data_t *ws = malloc(sizeof(w_data_t));

    if (ws == NULL)
        return NULL;
    ws->win = sfRenderWindow_create((sfVideoMode){WIN_WIDTH, WIN_HEIGHT,
        BITS_PER_PIXEL}, "My Paint", sfDefaultStyle, NULL);
    ws->w_content = init_win_content();
    return ws;
}
