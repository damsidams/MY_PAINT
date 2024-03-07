/*
** EPITECH PROJECT, 2024
** MY LIB
** File description:
** Converts a positive number from int to str in the given base
*/

#include <stdlib.h>

static int get_nb_size(int *nb, int base)
{
    int size = 1;
    int tmp = *nb;

    while (tmp / base > 0) {
        tmp /= base;
        size++;
    }
    return size;
}

char *my_nb_to_str_base(int nb, int base)
{
    int size = get_nb_size(&nb, base);
    char *str_nb = malloc(sizeof(char) * (size + 1));
    char *array = "0123456789abcdef";
    int i = size - 1;

    str_nb[size] = '\0';
    while (i >= 0) {
        str_nb[i] = array[nb % base];
        nb /= base;
        i--;
    }
    return str_nb;
}
