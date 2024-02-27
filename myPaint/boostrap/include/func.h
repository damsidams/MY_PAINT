/*
** EPITECH PROJECT, 2023
** func
** File description:
** prototype of func used in the project
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <SFML/Graphics.h>
#include <SFML/System.h>
#include <SFML/Window.h>

#ifndef MY_FUNC_H
    #define MY_FUNC_H
struct button_s {
    sfRectangleShape *rect ;
    sfBool (*is_clicked)(struct button_s *, sfMouseButtonEvent *);
    sfBool (*is_hover)(struct button_s *, sfMouseMoveEvent *);
};
#endif /* MY_FUNC_H */
