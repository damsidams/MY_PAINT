/*
** EPITECH PROJECT, 2024
** MY PAINT
** File description:
** Function to free everyting
*/

#include <stdlib.h>
#include <SFML/Graphics.h>
#include "header.h"

static void free_button(b_content_t *button)
{
    if (button == NULL)
        return;
    sfRectangleShape_destroy(button->rect);
    if (button->txt != NULL)
        sfText_destroy(button->txt);
    if (button->texture != NULL)
        sfTexture_destroy(button->texture);
}

static void free_list(options_t *list)
{
    options_t *next = NULL;

    while (list != NULL) {
        next = list->next;
        free_button(list->button);
        free(list);
        list = next;
    }
    free(list);
}

static void free_drop_menu(drop_menu_t *dm)
{
    if (dm == NULL)
        return;
    if (dm->button != NULL)
        free_button(dm->button);
    free_list(dm->options);
    free(dm);
}

static void free_toolbar(toolbar_t *toolbar)
{
    sfSprite_destroy(toolbar->sprite);
    sfImage_destroy(toolbar->image);
    sfTexture_destroy(toolbar->texture);
    free_list(toolbar->tool_list);
    free_list(toolbar->shape_list);
    free_drop_menu(toolbar->size_selector);
    sfRectangleShape_destroy(toolbar->color_picker->rect);
    sfTexture_destroy(toolbar->color_picker->texture);
    sfImage_destroy(toolbar->color_picker->image);
    free(toolbar->color_picker);
    free(toolbar);
}

void free_everything(w_data_t *w_data)
{
    for (unsigned int i = 0; w_data->w_content->menu[i]; i++)
        free_drop_menu(w_data->w_content->menu[i]);
    free_toolbar(w_data->w_content->toolbar);
    sfImage_destroy(w_data->w_content->image);
    sfSprite_destroy(w_data->w_content->sprite);
    sfTexture_destroy(w_data->w_content->texture);
    free(w_data->w_content->draw);
    sfRenderWindow_destroy(w_data->win);
    free(w_data->w_content);
    free(w_data);
}
