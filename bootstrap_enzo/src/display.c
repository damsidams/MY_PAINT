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
        if (drop_menu[i]->button->txt != NULL)
            sfRenderWindow_drawText(win, drop_menu[i]->button->txt, sfFalse);
    }
    return SUCCESS;
}
