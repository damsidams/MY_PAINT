/*
** EPITECH PROJECT, 2024
** MY PAINT
** File description:
** Functions to display
*/

#include <SFML/Graphics.h>
#include "header.h"

int display_top_bar(sfRenderWindow *win, drop_menu_t **drop_menu)
{
    if (win == NULL || drop_menu == NULL)
        return ERROR;
    for (unsigned int i = 0; drop_menu[i] != NULL; i++) {
        sfRenderWindow_drawRectangleShape
            (win, drop_menu[i]->button->rect, NULL);
        if (drop_menu[i]->button->txt != NULL)
            sfRenderWindow_drawText(win, drop_menu[i]->button->txt, sfFalse);
    }
    return SUCCESS;
}

static int display_tool_list(sfRenderWindow *win, options_t *tool_list)
{
    while (tool_list != NULL) {
        sfRenderWindow_drawRectangleShape(win, tool_list->button->rect, NULL);
        tool_list = tool_list->next;
    }
    return SUCCESS;
}

static int display_size_selectors(sfRenderWindow *win, drop_menu_t *dm)
{
    options_t *list = dm->options;

    if (dm == NULL) {
        my_putstr_err("Error: size selector list is null\n");
        return ERROR;
    }
    while (list != NULL) {
        sfRenderWindow_drawRectangleShape
            (win, list->button->rect, sfFalse);
        sfRenderWindow_drawText(win, list->button->txt, sfFalse);
        list = list->next;
    }
    return SUCCESS;
}

static int display_shape_selectors(sfRenderWindow *win, options_t *shape_list)
{
    options_t *list = shape_list;

    if (shape_list == NULL) {
        my_putstr_err("Error: shape selector list is null\n");
        return ERROR;
    }
    while (list != NULL) {
        sfRenderWindow_drawRectangleShape
            (win, list->button->rect, sfFalse);
        list = list->next;
    }
    return SUCCESS;
}

int display_tool_bar(sfRenderWindow *win, toolbar_t *toolbar)
{
    if (win == NULL || toolbar == NULL) {
        my_putstr_err("Error: can't display toolbar\n");
        return ERROR;
    }
    sfRenderWindow_drawSprite(win, toolbar->sprite, sfFalse);
    display_tool_list(win, toolbar->tool_list);
    display_size_selectors(win, toolbar->size_selector);
    display_shape_selectors(win, toolbar->shape_list);
    sfRenderWindow_drawRectangleShape
        (win, toolbar->color_picker->rect, sfFalse);
    return SUCCESS;
}

void display(w_data_t *w_data)
{
    sfRenderWindow_drawSprite
            (w_data->win, w_data->w_content->sprite, NULL);
    display_top_bar(w_data->win, w_data->w_content->menu);
    display_tool_bar(w_data->win, w_data->w_content->toolbar);
    if (w_data->w_content->help != NULL)
        sfRenderWindow_drawSprite(w_data->win, w_data->w_content->help, NULL);
}
