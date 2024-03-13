/*
** EPITECH PROJECT, 2024
** MY_PAINT
** File description:
** Functions related to top menu
*/

#include <SFML/Graphics.h>
#include <stdlib.h>
#include "header.h"

void save_file(w_data_t *w_data)
{
    sfImage_saveToFile(w_data->w_content->image, "creation.jpg");
}
