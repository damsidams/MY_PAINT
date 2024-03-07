/*
** EPITECH PROJECT, 2023
** MY_RADAR
** File description:
** Main of my_radar
*/

#include <SFML/Graphics.h>
#include <SFML/Config.h>
#include <stdlib.h>
#include "header.h"

static sfBool check_click(struct s_gui_object *button, sfMouseButtonEvent *event)
{
    sfFloatRect tmp_rect = sfRectangleShape_getGlobalBounds(button->rect);

    if (sfFloatRect_contains(&tmp_rect, event->x, event->y)) {
        button->state = PRESSED;
        return sfTrue;
    }
    return sfFalse;
}

static sfBool is_hover(struct s_gui_object *button, sfMouseMoveEvent *event)
{
    sfFloatRect tmp_rect = sfRectangleShape_getGlobalBounds(button->rect);

    if (sfFloatRect_contains(&tmp_rect, event->x, event->y)) {
        button->state = HOVER;
        return sfTrue;
    }
    return sfFalse;
}

struct s_gui_object *init_button(sfVector2f position, sfVector2f size)
{
    sfRectangleShape *rect = sfRectangleShape_create();
    struct s_gui_object *button = malloc(sizeof(button));

    sfRectangleShape_setPosition(rect, position);
    sfRectangleShape_setSize(rect, size);
    sfRectangleShape_setFillColor(rect, sfWhite);
    button->rect = rect;
    button->is_clicked = &check_click;
    button->is_hover = &is_hover;
    return button;
}

static void analyse_events(sfRenderWindow *win, struct s_gui_object *button, sfEvent event)
{
    if (event.type == sfEvtClosed ||
        sfKeyboard_isKeyPressed(sfKeyEscape))
        sfRenderWindow_close(win);
    button->state = RELEASED;
    if (event.type == sfEvtMouseMoved) {
        if (button->is_hover(button, &event.mouseMove))
            sfRectangleShape_setFillColor(button->rect, sfGreen);
        else
            sfRectangleShape_setFillColor(button->rect, sfBlack);
    }
    if (event.type == sfEvtMouseButtonPressed) {
        if (button->is_clicked(button, &event.mouseButton))
            printf("Hello\n");
    }

}

static int loop(struct s_gui_drop_menu *menu)
{
    sfRenderWindow *win = sfRenderWindow_create((sfVideoMode){1080, 720, 32}, "My Paint", sfDefaultStyle, NULL);
    sfEvent event;

    menu = add_option_drop_menu(menu);
    menu = add_option_drop_menu(menu);
    menu = add_option_drop_menu(menu);
    while (sfRenderWindow_isOpen(win)) {
        sfRenderWindow_pollEvent(win, &event);
        analyse_events(win, menu->button, event);
        sfRenderWindow_display(win);
        sfRenderWindow_clear(win, sfWhite);
        sfRenderWindow_drawRectangleShape(win, menu->button->rect, NULL);
        //sfRenderWindow_drawRectangleShape(win, button->rect, NULL);
        if (IS_HOVER(menu->button))
            display_options(win, menu);
    }
    return 0;
}

int main(void)
{
    //struct s_gui_object *button = init_button((sfVector2f){0, 0}, (sfVector2f){100, 100});
    struct s_gui_drop_menu *menu = create_drop_menu((sfVector2f){0, 0}, (sfVector2f){100, 100});

    loop(menu);
    return 0;
}
