/*
** EPITECH PROJECT, 2024
** MY PAINT
** File description:
** Functions related to colors
*/

#include <SFML/Graphics.h>
#include <SFML/Config.h>
#include <stdlib.h>
#include "header.h"

void draw_zone(sfImage *image)
{
    sfVector2i start = {0,0};

    for (int x = 0; x < DRAW_WIDTH - start.x; x++) {
        sfImage_setPixel(image, start.x + x, start.y, sfRed);
        for (int y = 0; y < DRAW_HEIGHT - start.y; y++)
            sfImage_setPixel(image, start.x + x, start.y + y, sfRed);
    }
}
