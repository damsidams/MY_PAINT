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

static sfBool check_click(b_content_t *button,
    sfMouseButtonEvent *event)
{
    sfFloatRect tmp_rect = sfRectangleShape_getGlobalBounds(button->rect);

    if (sfFloatRect_contains(&tmp_rect, event->x, event->y)) {
        button->state = PRESSED;
        return sfTrue;
    }
    return sfFalse;
}

static sfBool is_hover(b_content_t *button, sfMouseMoveEvent *event)
{
    sfFloatRect tmp_rect = sfRectangleShape_getGlobalBounds(button->rect);

    if (sfFloatRect_contains(&tmp_rect, event->x, event->y)) {
        button->state = HOVER;
        return sfTrue;
    }
    return sfFalse;
}

b_content_t *init_button(sfVector2f position, sfVector2f size)
{
    sfRectangleShape *rect = sfRectangleShape_create();
    b_content_t *button = malloc(sizeof(button));

    sfRectangleShape_setPosition(rect, position);
    sfRectangleShape_setSize(rect, size);
    sfRectangleShape_setFillColor(rect, sfWhite);
    button->rect = rect;
    button->is_clicked = &check_click;
    button->is_hover = &is_hover;
    return button;
}

static void analyse_events(sfRenderWindow *win,
    b_content_t *button, sfEvent event)
{
    if (event.type == sfEvtClosed ||
        sfKeyboard_isKeyPressed(sfKeyEscape))
        sfRenderWindow_close(win);
    button->state = RELEASED;
    if (event.type == sfEvtMouseMoved) {
        if (button->is_hover(button, &event.mouseMove))
            sfRectangleShape_setFillColor(button->rect, sfGreen);
        else
            sfRectangleShape_setFillColor(button->rect, sfBlack);
    }
    if (event.type == sfEvtMouseButtonPressed) {
        if (button->is_clicked(button, &event.mouseButton))
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

    w_data->w_content->menu = add_option_drop_menu(w_data->w_content->menu);
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
