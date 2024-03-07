/*
** EPITECH PROJECT, 2024
** LIB
** File description:
** The strdup() function returns a pointer to a new string which is a duplicate
** of the string s.  Memory for the new string is obtained with malloc(3),
** and can be freed with free(3).
*/

#include <stdlib.h>
#include <stddef.h>
#include "my.h"

char *my_strdup(const char *str)
{
    char *dup;
    int i = 0;

    if (str == NULL)
        return NULL;
    dup = malloc(sizeof(char) * (my_strlen(str) + 1));
    if (dup == NULL)
        return NULL;
    while (str[i]) {
        dup[i] = str[i];
        i++;
    }
    dup[i] = '\0';
    return dup;
}
