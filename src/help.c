/*
** EPITECH PROJECT, 2024
** MY PAINT
** File description:
** none
*/

#include <SFML/Graphics.h>
#include "header.h"

static void help(win_content_t *wc)
{
    sfVector2f position = {WIN_WIDTH / 2 - HELP_MSG_WIDTH / 2,
        WIN_HEIGHT / 2 - HELP_MSG_HEIGHT / 2};
    sfSprite *helpSprite = NULL;
    sfTexture *img = NULL;

    if (wc->help != NULL)
        return;
    helpSprite = sfSprite_create();
    img = sfTexture_createFromFile(HELP_PNG_PATH, NULL);
    sfSprite_setTexture(helpSprite, img, sfTrue);
    sfSprite_setTextureRect
        (helpSprite, (sfIntRect){0, 0, HELP_WIDTH, HELP_HEIGHT});
    sfSprite_setScale(helpSprite, (sfVector2f){1, 1});
    sfSprite_setPosition(helpSprite, position);
    wc->help = helpSprite;
}

static void about(win_content_t *wc)
{
    sfVector2f position = {WIN_WIDTH / 2 - ABOUT_WIDTH / 2,
        WIN_HEIGHT / 2 - ABOUT_HEIGHT / 2};
    sfSprite *helpSprite = NULL;
    sfTexture *img = NULL;

    if (wc->help != NULL)
        return;
    helpSprite = sfSprite_create();
    img = sfTexture_createFromFile
        (ABOUT_PNG_PATH, NULL);
    sfSprite_setTexture(helpSprite, img, sfTrue);
    sfSprite_setTextureRect
        (helpSprite, (sfIntRect){0, 0, ABOUT_WIDTH, ABOUT_HEIGHT});
    sfSprite_setScale(helpSprite, (sfVector2f){1, 1});
    sfSprite_setPosition(helpSprite, position);
    wc->help = helpSprite;
}

static void check_reset(win_content_t *wc, options_t *list)
{
    unsigned int pressed = 0;

    while (list != NULL) {
        if (list->button->rank == 2 && IS_PRESSED(list->button))
            pressed++;
        if (list->button->rank == 1 && IS_PRESSED(list->button))
            pressed++;
        list = list->next;
    }
    if (pressed == 0) {
        sfSprite_destroy(wc->help);
        wc->help = NULL;
    }
}

void run_help_event(win_content_t *wc, drop_menu_t *dm)
{
    options_t *list = dm->options;

    if (wc->help == NULL)
        check_reset(wc, list);
    while (list != NULL) {
        if (list->button->rank == 2 && IS_PRESSED(list->button))
            help(wc);
        if (list->button->rank == 1 && IS_PRESSED(list->button))
            about(wc);
        if (IS_RELEASED(list->button))
            wc->help = NULL;
        list = list->next;
    }
}
