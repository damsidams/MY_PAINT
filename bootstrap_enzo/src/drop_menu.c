/*
** EPITECH PROJECT, 2024
** MY_PAINT
** File description:
** Functions related to drop menu
*/

#include <SFML/Graphics.h>
#include <stdlib.h>
#include "header.h"


static int display_options(sfRenderWindow *win, drop_menu_t *menu)
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

int run_top_bar_event(sfRenderWindow *win, drop_menu_t **menu)
{
    for (unsigned int i = 0; menu[i] != NULL; i++) {
        if (IS_HOVER(menu[i]->button))
            display_options(win, menu[i]);
    }
    return SUCCESS;
}

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
    else if (mode == Image)
        set_rect_img(op->option, text);
    sfRectangleShape_setFillColor(op->option->rect, sfWhite);
    drop_menu->options = op;
    button_nb++;
    return drop_menu;
}

static drop_menu_t *init_file_dm(drop_menu_t *drop_menu, sfVector2f position,
    sfVector2f size)
{
    drop_menu->button = init_button(position, size);
    drop_menu->options = NULL;
    set_rect_text(drop_menu->button, drop_menu->button->rect, "File", FONT_SIZE);
    add_option_drop_menu(drop_menu, "New file", Text);
    add_option_drop_menu(drop_menu, "Open file", Text);
    add_option_drop_menu(drop_menu, "Save file", Text);
    return drop_menu;
}

static drop_menu_t *init_edit_dm(drop_menu_t *drop_menu, sfVector2f position,
    sfVector2f size)
{
    drop_menu->button = init_button(position, size);
    drop_menu->options = NULL;
    set_rect_text(drop_menu->button, drop_menu->button->rect, "Edit", FONT_SIZE);
    add_option_drop_menu(drop_menu, PENCIL_PNG_PATH, Image);
    add_option_drop_menu(drop_menu, ERASER_PNG_PATH, Image);
    return drop_menu;
}

static drop_menu_t *init_help_dm(drop_menu_t *drop_menu, sfVector2f position,
    sfVector2f size)
{
    drop_menu->button = init_button(position, size);
    drop_menu->options = NULL;
    set_rect_text(drop_menu->button, drop_menu->button->rect, "Help", FONT_SIZE);
    add_option_drop_menu(drop_menu, "About", Text);
    add_option_drop_menu(drop_menu, "Help", Text);
    return drop_menu;
}

drop_menu_t **create_drop_menu(sfVector2f position, sfVector2f size)
{
    drop_menu_t **drop_menu = malloc(sizeof(drop_menu_t) * (DROP_MENU_NB + 1));
    drop_menu_t *file_dm = malloc(sizeof(drop_menu_t));
    drop_menu_t *edit_dm = malloc(sizeof(drop_menu_t));
    drop_menu_t *help_dm = malloc(sizeof(drop_menu_t));

    drop_menu[0] = init_file_dm(file_dm, (sfVector2f)
        {position.x + size.x * 0, position.y}, size);
    drop_menu[1] = init_edit_dm(edit_dm, (sfVector2f)
        {position.x + size.x * 1, position.y}, size);
    drop_menu[2] = init_help_dm(help_dm, (sfVector2f)
        {position.x + size.x * 2, position.y}, size);
    drop_menu[3] = NULL;
    return drop_menu;
}
