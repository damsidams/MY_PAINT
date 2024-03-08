/*
** EPITECH PROJECT, 2024
** MY_PAINT
** File description:
** Functions related to drop menu
*/

#include <SFML/Graphics.h>
#include <stdlib.h>
#include "header.h"

drop_menu_t *create_drop_menu(sfVector2f position, sfVector2f size)
{
    drop_menu_t *drop_menu = malloc(sizeof(drop_menu_t));

    drop_menu->button = init_button(position, size);
    drop_menu->options = NULL;
    return drop_menu;
}

drop_menu_t *add_option_drop_menu(drop_menu_t *drop_menu)
{
    options_t *op = malloc(sizeof(options_t));
    sfRectangleShape *rect = drop_menu->button->rect;
    sfVector2f pos = sfRectangleShape_getPosition(rect);
    sfVector2f size = sfRectangleShape_getSize(rect);
    static int button_nb = 1;

    pos.y += size.y * button_nb;
    op->option = init_button(pos, size);
    op->next = drop_menu->options;
    sfRectangleShape_setFillColor(op->option->rect, sfBlue);
    drop_menu->options = op;
    button_nb++;
    return drop_menu;
}

int display_options(sfRenderWindow *win, drop_menu_t *menu)
{
    options_t *option;

    if (menu == NULL)
        return ERROR;
    option = menu->options;
    while (option != NULL) {
        sfRenderWindow_drawRectangleShape(win, option->option->rect, NULL);
        option = option->next;
    }
    return SUCCESS;
}
