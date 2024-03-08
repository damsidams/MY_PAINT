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

static void analyse_events(sfRenderWindow *win,
    b_content_t *button, sfEvent event)
{
    if (event.type == sfEvtClosed ||
        sfKeyboard_isKeyPressed(sfKeyEscape))
        sfRenderWindow_close(win);
    button->state = RELEASED;
    if (event.type == sfEvtMouseMoved) {
        if ((*button->is_hover)(button, &event.mouseMove))
            sfRectangleShape_setFillColor(button->rect, sfGreen);
        else
            sfRectangleShape_setFillColor(button->rect, sfBlack);
    }
    if (event.type == sfEvtMouseButtonPressed) {
        if ((*button->is_clicked)(button, &event.mouseButton))
            printf("Hello\n");
    }
}

static void draw_line(sfImage *image, sfVector2i initial_pos,
    int line_length, sfColor color)
{
    for (int i = 0; i < WIN_WIDTH && i < line_length; i++)
        sfImage_setPixel(image, initial_pos.x + i, initial_pos.y, color);
}

static int loop(w_data_t *w_data)
{
    sfEvent event;

    draw_line(w_data->w_content->image, (sfVector2i){105, 50}, 150, sfRed);
    draw_line(w_data->w_content->image, (sfVector2i){105, 51}, 150, sfRed);
    draw_line(w_data->w_content->image, (sfVector2i){105, 52}, 150, sfRed);
    draw_line(w_data->w_content->image, (sfVector2i){105, 53}, 150, sfRed);
    sfTexture_updateFromImage(w_data->w_content->texture, w_data->w_content->image, 0, 0);
    while (sfRenderWindow_isOpen(w_data->win)) {
        sfRenderWindow_pollEvent(w_data->win, &event);
        analyse_events(w_data->win,
            w_data->w_content->menu->button, event);
        sfRenderWindow_display(w_data->win);
        sfRenderWindow_clear(w_data->win, sfWhite);
        sfRenderWindow_drawRectangleShape(w_data->win,
            w_data->w_content->menu->button->rect, NULL);
        sfRenderWindow_drawSprite
            (w_data->win, w_data->w_content->sprite, sfFalse);
        if (IS_HOVER(w_data->w_content->menu->button))
            display_options(w_data->win, w_data->w_content->menu);
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
