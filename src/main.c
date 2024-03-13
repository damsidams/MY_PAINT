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

static int loop(w_data_t *w_data)
{
    sfEvent event;

    draw_zone(w_data->w_content->image, sfWhite);
    sfTexture_updateFromImage
        (w_data->w_content->texture, w_data->w_content->image, 0, 0);
    while (sfRenderWindow_isOpen(w_data->win)) {
        draw_or_not(w_data);
        sfRenderWindow_pollEvent(w_data->win, &event);
        analyse_events(w_data->win,
            w_data->w_content, &event);
        sfRenderWindow_clear(w_data->win, sfWhite);
        display_top_bar(w_data->win, w_data->w_content->menu);
        display_tool_bar(w_data->win, w_data->w_content->toolbar);
        sfRenderWindow_drawSprite
            (w_data->win, w_data->w_content->sprite, NULL);
        sfRenderWindow_display(w_data->win);
    }
    save_file(w_data);
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
