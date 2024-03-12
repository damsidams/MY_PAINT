/*
** EPITECH PROJECT, 2023
** MY_RADAR
** File description:
** Main of my_radar
*/

#include <SFML/Graphics.h>
#include <SFML/Config.h>
#include <stdlib.h>
#include "header.h"

static void draw_line(sfImage *image, sfVector2i initial_pos,
    int line_length, sfColor color)
{
    for (int i = 0; i < WIN_WIDTH && i < line_length; i++)
        sfImage_setPixel(image, initial_pos.x + i, initial_pos.y, color);
}

static int loop(w_data_t *w_data)
{
    sfEvent event;

    /*draw_line(w_data->w_content->image, (sfVector2i){105, 50}, 150, sfRed);
    draw_line(w_data->w_content->image, (sfVector2i){105, 51}, 150, sfRed);
    draw_line(w_data->w_content->image, (sfVector2i){105, 52}, 150, sfRed);
    draw_line(w_data->w_content->image, (sfVector2i){105, 53}, 150, sfRed);*/
    sfTexture_updateFromImage(w_data->w_content->texture, w_data->w_content->image, 0, 0);
    while (sfRenderWindow_isOpen(w_data->win)) {
        sfRenderWindow_pollEvent(w_data->win, &event);
        analyse_events(w_data->win,
            w_data->w_content, &event);
        sfRenderWindow_display(w_data->win);
        sfRenderWindow_clear(w_data->win, sfWhite);
        display_top_bar(w_data->win, w_data->w_content->menu);
        sfRenderWindow_drawSprite
            (w_data->win, w_data->w_content->sprite, sfFalse);
    }
    return SUCCESS;
}

int main(void)
{
    w_data_t *w_data = init_win();

    if (w_data == NULL)
        return ERROR;
    loop(w_data);
    return 0;
}
