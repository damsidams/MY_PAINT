/*
** EPITECH PROJECT, 2024
** MY PAINT
** File description:
** functions related to events
*/

#include <SFML/Graphics.h>
#include "header.h"

static void analyse_top_bar_event(drop_menu_t **menu, sfEvent *event)
{
    for (unsigned int i = 0; menu[i] != NULL; i++) {
        if (event->type == sfEvtMouseMoved)
            (*(menu[i])->button->is_hover)((menu[i]->button), &event->mouseMove);
        if (event->type == sfEvtMouseButtonPressed)
            (*(menu[i])->button->is_clicked)((menu[i]->button), &event->mouseButton);
    }
}

void analyse_events(sfRenderWindow *win,
    win_content_t *wc, sfEvent *event)
{
    if (event->type == sfEvtClosed ||
        sfKeyboard_isKeyPressed(sfKeyEscape))
        sfRenderWindow_close(win);
    analyse_top_bar_event(wc->menu, event);
    run_top_bar_event(win, wc->menu);
}
