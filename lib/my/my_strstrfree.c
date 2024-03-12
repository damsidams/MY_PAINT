/*
** EPITECH PROJECT, 2024
** MY LIB
** File description:
** Free a char ** function
*/

#include <stdlib.h>
#include "my.h"

void my_strstrfree(char **array)
{
    int i = 0;

    while (array[i]) {
        free(array[i]);
        i++;
    }
    free(array);
}
