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
        if (option_list->button->txt != NULL) {
            sfRenderWindow_drawText(win, option_list->button->txt, NULL);
            //printf("txt: %s\n", sfText_getString(option_list->button->txt));
        }
        if (option_list->button->texture != NULL)
            sfRenderWindow_drawRectangleShape
                (win, option_list->button->rect, NULL);
        option_list = option_list->next;
    }
    return SUCCESS;
}

int run_top_bar_event(sfRenderWindow *win, drop_menu_t **menu)
{
    for (unsigned int i = 0; menu[i] != NULL; i++) {
        if (IS_HOVER(menu[i]->button) || IS_PRESSED(menu[i]->button))
            display_options(win, menu[i]);
        if (i == 2)
            run_help_event(menu[i]);
    }
    return SUCCESS;
}

drop_menu_t *add_option_drop_menu(drop_menu_t *drop_menu, char const *text,
    enum init_mode mode, int rank_nb)
{
    options_t *op = malloc(sizeof(options_t));
    sfRectangleShape *rect = drop_menu->button->rect;
    sfVector2f pos = sfRectangleShape_getPosition(rect);
    sfVector2f size = sfRectangleShape_getSize(rect);

    drop_menu->button->rank = rank_nb;
    pos.y += size.y * rank_nb;
    op->button = init_button(pos, size);
    op->next = drop_menu->options;
    //printf("x: %f, y :%f\n", pos.x, pos.y);
    if (mode == Text) {
        set_rect_text(op->button, op->button->rect, text, FONT_SIZE);
        //printf("texte is set: %s\n", text);
    } else if (mode == Image)
        set_rect_img(op->button, text);
    sfRectangleShape_setFillColor(op->button->rect, sfWhite);
    drop_menu->options = op;
    return drop_menu;
}

static drop_menu_t *init_file_dm(drop_menu_t *drop_menu, sfVector2f position,
    sfVector2f size)
{
    drop_menu->button = init_button(position, size);
    drop_menu->options = NULL;
    set_rect_text(drop_menu->button,
        drop_menu->button->rect, "File", FONT_SIZE);
    add_option_drop_menu(drop_menu, "New file", Text, 1);
    add_option_drop_menu(drop_menu, "Open file", Text, 2);
    add_option_drop_menu(drop_menu, "Save file", Text, 3);
    return drop_menu;
}

static drop_menu_t *init_edit_dm(drop_menu_t *drop_menu, sfVector2f position,
    sfVector2f size)
{
    drop_menu->button = init_button(position, size);
    drop_menu->options = NULL;
    set_rect_text
        (drop_menu->button, drop_menu->button->rect, "Edit", FONT_SIZE);
    add_option_drop_menu(drop_menu, PENCIL_PNG_PATH, Image, 1);
    add_option_drop_menu(drop_menu, ERASER_PNG_PATH, Image, 2);
    return drop_menu;
}

static drop_menu_t *init_help_dm(drop_menu_t *drop_menu, sfVector2f position,
    sfVector2f size)
{
    drop_menu->button = init_button(position, size);
    drop_menu->options = NULL;
    set_rect_text
        (drop_menu->button, drop_menu->button->rect, "Help", FONT_SIZE);
    add_option_drop_menu(drop_menu, "About", Text, 1);
    add_option_drop_menu(drop_menu, "Help", Text, 2);
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
