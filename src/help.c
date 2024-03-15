/*
** EPITECH PROJECT, 2024
** MY PAINT
** File description:
** none
*/

#include <SFML/Graphics.h>
#include "header.h"

sfSprite *help(void)
{
    sfVector2f position;
    sfSprite *helpSprite = sfSprite_create();
    sfTexture *img = sfTexture_createFromFile
        (HELP_PNG_PATH, NULL);

    sfSprite_setTexture(helpSprite, img, sfTrue);
    sfSprite_setTextureRect
        (helpSprite, (sfIntRect){0, 0, 485, 307});
    sfSprite_setScale(helpSprite, (sfVector2f){1, 1});
    sfSprite_setPosition(helpSprite, position);
    return helpSprite;
}

sfSprite *about(void)
{
    sfVector2f position;
    sfSprite *helpSprite = sfSprite_create();
    sfTexture *img = sfTexture_createFromFile
        (ABOUT_PNG_PATH, NULL);

    sfSprite_setTexture(helpSprite, img, sfTrue);
    sfSprite_setTextureRect
        (helpSprite, (sfIntRect){0, 0, 251, 51});
    sfSprite_setScale(helpSprite, (sfVector2f){1, 1});
    sfSprite_setPosition(helpSprite, position);
    return helpSprite;
}

void run_help_event(drop_menu_t *dm)
{
    options_t *list = dm->options;

    while (list != NULL && list->button->rank != 2)
        list = list->next;
    if (list == NULL)
        return;
    if (IS_PRESSED(list->button))
        help();
}

void run_about_event(drop_menu_t *dm)
{
    options_t *list = dm->options;

    while (list != NULL && list->button->rank != 1)
        list = list->next;
    if (list == NULL)
        return;
    if (IS_PRESSED(list->button))
        about();
}

