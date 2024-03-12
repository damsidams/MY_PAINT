/*
** EPITECH PROJECT, 2024
** MY PAINT
** File description:
** Functions related to colors
*/

#include <stdlib.h>
#include "header.h"

sfUint8 *init_pixel_array(void)
{
    return malloc((sizeof(sfUint8) * 4) * (DRAW_WIDTH * DRAW_HEIGHT + 1));
}
