/*
** EPITECH PROJECT, 2024
** MY PAINT
** File description:
** Functions related to colors
*/

#include "header.h"

sfUint8 *init_pixel_array(void)
{
    return malloc((sizeof(sfUint8) * 4) * (WIN_WIDTH * WIN_HEIGHT + 1));
}
