/*
** EPITECH PROJECT, 2024
** MY PAINT
** File description:
** functions related to events
*/

#include <SFML/Graphics.h>
#include "header.h"

static void analyse_top_section_event(drop_menu_t *menu, sfEvent *event)
{
    options_t *list = menu->options;

    while (list != NULL) {
        if (event->type == sfEvtMouseMoved)
            list->button->is_hover(list->button, &event->mouseMove);
        if (event->type == sfEvtMouseButtonPressed)
            list->button->is_clicked(list->button, &event->mouseButton);
        list = list->next;
    }
}

static void analyse_top_bar_event(drop_menu_t **menu, sfEvent *event)
{
    for (unsigned int i = 0; menu[i] != NULL; i++) {
        if (event->type == sfEvtMouseMoved)
            (*(menu[i])->button->is_hover)
                ((menu[i]->button), &event->mouseMove);
        if (event->type == sfEvtMouseButtonPressed)
            (*(menu[i])->button->is_clicked)
                ((menu[i]->button), &event->mouseButton);
        analyse_top_section_event(menu[i], event);
    }
}

static void shape_selector_event(toolbar_t *toolbar, sfEvent *event)
{
    options_t *list = toolbar->shape_list;

    while (list != NULL) {
        if (event->type == sfEvtMouseMoved)
            list->button->is_hover(list->button, &event->mouseMove);
        if (event->type == sfEvtMouseButtonPressed)
            list->button->is_clicked(list->button, &event->mouseButton);
        list = list->next;
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
    shape_selector_event(toolbar, event);
}

static void run_toolselector_event(win_content_t *wc)
{
    unsigned int tool_nb = 0;
    options_t *list = wc->toolbar->tool_list;

    while (list != NULL) {
        if (IS_HOVER(list->button) || IS_PRESSED(list->button)
            || tool_nb == wc->draw->draw_mode)
            sfRectangleShape_setOutlineColor(list->button->rect, sfYellow);
        else
            sfRectangleShape_setOutlineColor(list->button->rect, sfBlack);
        if (IS_PRESSED(list->button))
            wc->draw->draw_mode = tool_nb;
        tool_nb++;
        list = list->next;
    }
}

static void run_size_selector_event(win_content_t *wc)
{
    options_t *list = wc->toolbar->size_selector->options;

    while (list != NULL) {
        if (IS_HOVER(list->button) || IS_PRESSED(list->button)
            || array_size(list->button->rank) == wc->draw->size)
            sfRectangleShape_setOutlineColor(list->button->rect, sfYellow);
        else
            sfRectangleShape_setOutlineColor(list->button->rect, sfBlack);
        if (IS_PRESSED(list->button))
            wc->draw->size = array_size(list->button->rank);
        list = list->next;
    }
}

static void run_shape_selector_event(win_content_t *wc)
{
    unsigned int shape_nb = 0;
    options_t *list = wc->toolbar->shape_list;

    while (list != NULL) {
        if (IS_HOVER(list->button) || IS_PRESSED(list->button)
            || shape_nb == wc->draw->shape)
            sfRectangleShape_setOutlineColor(list->button->rect, sfYellow);
        else
            sfRectangleShape_setOutlineColor(list->button->rect, sfBlack);
        if (IS_PRESSED(list->button))
            wc->draw->shape = list->button->rank;
        shape_nb++;
        list = list->next;
    }
}

int run_tool_bar_event(win_content_t *wc)
{
    run_toolselector_event(wc);
    run_size_selector_event(wc);
    run_shape_selector_event(wc);
    return SUCCESS;
}

void analyse_events(sfRenderWindow *win,
    win_content_t *wc, sfEvent *event)
{
    if (event->type == sfEvtClosed ||
        sfKeyboard_isKeyPressed(sfKeyEscape))
        sfRenderWindow_close(win);
    analyse_top_bar_event(wc->menu, event);
    run_top_bar_event(wc, win, wc->menu);
    analyse_tool_bar_event(wc->toolbar, event);
    color_pick_event(wc, wc->toolbar, event);
    run_tool_bar_event(wc);
}
