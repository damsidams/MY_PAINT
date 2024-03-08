/*
** EPITECH PROJECT, 2024
** MY PAINT
** File description:
** none
*/

#include <stdlib.h>
#include <SFML/Graphics.h>
#include "header.h"

static win_content_t *init_win_content(void)
{
    win_content_t *wc = malloc(sizeof(win_content_t));
    sfUint8 *buffer = init_pixel_array();
    sfIntRect image_rect = {0, 0, WIN_WIDTH, WIN_HEIGHT};

    if (buffer == NULL || wc == NULL)
        return NULL;
    wc->menu = create_drop_menu((sfVector2f){0, 0}, (sfVector2f){100, 100});
    wc->image = sfImage_createFromPixels(WIN_WIDTH, WIN_HEIGHT, buffer);
    wc->sprite = sfSprite_create();
    wc->texture = sfTexture_createFromImage(wc->image, &image_rect);
    sfSprite_setTexture(wc->sprite, wc->texture, sfTrue);
    sfSprite_setTextureRect(wc->sprite, image_rect);
    printf("image is innit\n");
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
