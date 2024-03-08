/*
** EPITECH PROJECT, 2024
** MY_PAINT
** File description:
** Functions related to drop menu
*/

#include <SFML/Graphics.h>
#include <stdlib.h>
#include "header.h"

drop_menu_t *add_option_drop_menu(drop_menu_t *drop_menu, char const *text,
    enum init_mode mode)
{
    options_t *op = malloc(sizeof(options_t));
    sfRectangleShape *rect = drop_menu->button->rect;
    sfVector2f pos = sfRectangleShape_getPosition(rect);
    sfVector2f size = sfRectangleShape_getSize(rect);
    static int button_nb = 1;

    pos.y += size.y * button_nb;
    op->option = init_button(pos, size);
    op->next = drop_menu->options;
    if (mode == Text)
        set_rect_text(op->option, op->option->rect, text, FONT_SIZE);
    sfRectangleShape_setFillColor(op->option->rect, sfWhite);
    drop_menu->options = op;
    button_nb++;
    return drop_menu;
}

int display_options(sfRenderWindow *win, drop_menu_t *menu)
{
    options_t *option_list;

    if (menu == NULL)
        return ERROR;
    option_list = menu->options;
    while (option_list != NULL) {
        sfRenderWindow_drawRectangleShape(win, option_list->option->rect, NULL);
        if (option_list->option->txt != NULL)
            sfRenderWindow_drawText(win, option_list->option->txt, NULL);
        option_list = option_list->next;
    }
    return SUCCESS;
}

drop_menu_t *create_drop_menu(sfVector2f position, sfVector2f size)
{
    drop_menu_t *drop_menu = malloc(sizeof(drop_menu_t));

    drop_menu->button = init_button(position, size);
    drop_menu->options = NULL;
    add_option_drop_menu(drop_menu, "New file", Text);
    add_option_drop_menu(drop_menu, "Open file", Text);
    add_option_drop_menu(drop_menu, "Save file", Text);
    return drop_menu;
}
