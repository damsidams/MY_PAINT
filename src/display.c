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
        sfRenderWindow_drawRectangleShape(win, tool_list->option->rect, NULL);
        tool_list = tool_list->next;
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
    return SUCCESS;
}
