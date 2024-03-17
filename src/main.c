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
        sfRenderWindow_display(w_data->win);
        sfRenderWindow_clear(w_data->win, sfWhite);
        display(w_data);
    }
    return SUCCESS;
}

int main(int ac, char **av)
{
    w_data_t *w_data = NULL;

    (void)av;
    if (ac != 1)
        return ERROR;
    w_data = init_win();
    if (w_data == NULL)
        return ERROR;
    loop(w_data);
    free_everything(w_data);
    return SUCCESS;
}
