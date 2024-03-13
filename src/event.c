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
            (*(menu[i])->button->is_hover)
                ((menu[i]->button), &event->mouseMove);
        if (event->type == sfEvtMouseButtonPressed)
            (*(menu[i])->button->is_clicked)
                ((menu[i]->button), &event->mouseButton);
    }
}

static void analyse_tool_bar_event(toolbar_t *toolbar, sfEvent *event)
{
    options_t *list = toolbar->tool_list;
    options_t *s_list = toolbar->size_selector->options;

    while (list != NULL) {
        if (event->type == sfEvtMouseMoved)
            list->button->is_hover(list->button, &event->mouseMove);
        if (event->type == sfEvtMouseButtonPressed)
            list->button->is_clicked(list->button, &event->mouseButton);
        list = list->next;
    }
    while (s_list != NULL) {
        if (event->type == sfEvtMouseMoved)
            s_list->button->is_hover(s_list->button, &event->mouseMove);
        if (event->type == sfEvtMouseButtonPressed)
            s_list->button->is_clicked(s_list->button, &event->mouseButton);
        s_list = s_list->next;
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
    analyse_tool_bar_event(wc->toolbar, event);
}
