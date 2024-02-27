/*
** EPITECH PROJECT, 2023
** my_strcat
** File description:
** concatenate 2 strings
*/

#include <stdlib.h>
#include "my.h"

void all(int *counter, char **res, char *str1, char *str2)
{
    int counter2 = 0;

    while (counter2 < my_strlen(str1)){
        (*res)[*counter] = str1[counter2];
        counter2++;
        (*counter)++;
    }
    counter2 = 0;
    while (counter2 < my_strlen(str2)){
        (*res)[*counter] = str2[counter2];
        counter2++;
        *counter = *counter + 1;
    }
}

char *my_strcat(char *str1, char *str2)
{
    char *res;
    int total_lenght = 0;
    int counter = 0;

    total_lenght = my_strlen(str1) + my_strlen(str2) + 1;
    res = malloc((sizeof(char)) * total_lenght);
    all(&counter, &res, str1, str2);
    res[total_lenght - 1] = '\0';
    return res;
}
