/*
** EPITECH PROJECT, 2024
** MY_PAINT
** File description:
** Functions related to top menu
*/

#include <SFML/Graphics.h>
#include <stdlib.h>
#include <stdbool.h>
#include "header.h"

static int wait_to_repeat(float sec_to_wait)
{
    static int first = 1;
    static sfClock *clock;
    sfTime elapsed;

    if (first) {
        clock = sfClock_create();
        first = 0;
        return true;
    }
    elapsed = sfClock_getElapsedTime(clock);
    if (sfTime_asSeconds(elapsed) >= sec_to_wait) {
        sfClock_restart(clock);
        return true;
    }
    return false;
}

static void save_file(win_content_t *wc)
{
    if (wait_to_repeat(SAVE_COOLDOWN)) {
        sfImage_saveToFile(wc->image, SAVE_NAME);
        mini_printf("Image saved as %s\n", SAVE_NAME);
    }
}

static void run_file_event(win_content_t *wc, drop_menu_t *dm)
{
    options_t *list = dm->options;

    while (list != NULL) {
        if (IS_HOVER(list->button))
            sfRectangleShape_setFillColor(list->button->rect, sfWhite);
        else
            sfRectangleShape_setFillColor
                (list->button->rect, sfColor_fromRGB(232, 213, 211));
        if (list->button->rank == 3 && IS_PRESSED(list->button))
            save_file(wc);
        list = list->next;
    }
}

int run_top_bar_event(win_content_t *wc,
    sfRenderWindow *win, drop_menu_t **menu)
{
    for (unsigned int i = 0; menu[i] != NULL; i++) {
        if (IS_HOVER(menu[i]->button) || IS_PRESSED(menu[i]->button))
            display_options(win, menu[i]);
        if (i == 0)
            run_file_event(wc, menu[i]);
        if (i == 2)
            run_help_event(menu[i]);
    }
    return SUCCESS;
}
