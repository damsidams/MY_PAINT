/*
** EPITECH PROJECT, 2024
** main
** File description:
** bootstrap main
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <SFML/Graphics.h>
#include <SFML/System.h>
#include <SFML/Window.h>
#include "func.h"

struct button_s *init_button( sfVector2f position, sfVector2f size)
{
    struct button_s *my_button = malloc(sizeof(struct button_s));

    my_button->rect = sfRectangleShape_create();
    sfRectangleShape_setSize(my_button->rect, size);
    sfRectangleShape_setPosition(my_button->rect, position);
    sfRectangleShape_setFillColor(my_button->rect, sfRed);
    return my_button;
}

sfBool is_button_clicked(struct button_s *my_button, sfMouseButtonEvent *mouse)
{

    sfFloatRect rect = sfRectangleShape_getGlobalBounds(my_button->rect);
    return sfFloatRect_contains(&rect, mouse->x, mouse->y);
}

sfBool is_button_hoover(struct button_s *my_button, sfMouseMoveEvent *mouse)
{

    sfFloatRect rect = sfRectangleShape_getGlobalBounds(my_button->rect);
    return sfFloatRect_contains(&rect, mouse->x, mouse->y);
}

void game_loop(sfRenderWindow *window, struct button_s *my_button)
{
    sfEvent event;

    while (sfRenderWindow_pollEvent(window, &event)) {
        if (event.type == sfEvtMouseButtonPressed ) {
            if (my_button->is_clicked(my_button, &event.mouseButton)) {
                puts(" Hello ");
                sfRectangleShape_setFillColor(my_button->rect, sfGreen);
            } else
                sfRectangleShape_setFillColor(my_button->rect, sfRed);
            continue;
        }
        if (event.type == sfEvtMouseMoved) {
            if (my_button->is_hover(my_button, &event.mouseMove)) {
                puts(" Hello World");
                sfRectangleShape_setFillColor(my_button->rect, sfYellow);
            } else
                sfRectangleShape_setFillColor(my_button->rect, sfRed);
                continue;
        }
        sfRectangleShape_setFillColor(my_button->rect, sfRed);
    }
    sfRenderWindow_clear(window, sfBlack);
    sfRenderWindow_drawRectangleShape(window, my_button->rect, NULL);
    sfRenderWindow_display(window);
    sfSleep((sfTime){10000});
}

int main(int argc, char **argv)
{
    sfVideoMode mode = {800, 600, 32};
    sfVector2f buttonPos = {40, 80};
    sfVector2f buttonSize = {20, 30};
    sfRenderWindow *window;
    struct button_s *my_button = init_button(buttonPos, buttonSize);

    my_button->is_clicked = is_button_clicked;
    my_button->is_hover = is_button_hoover;
    window = sfRenderWindow_create(mode, "CSFML boostrap", sfResize | sfClose, NULL);
    if (!window)
        return EXIT_FAILURE;
    
    while (sfRenderWindow_isOpen(window))
        game_loop(window, my_button);
    sfRenderWindow_destroy(window);
}
