/*
** EPITECH PROJECT, 2023
** my_strlowcase
** File description:
** puts every letter of every word in it in lowercase
*/

char *my_strlowcase(char *str)
{
    int i = 0;

    while (str[i] != '\0'){
        if (str[i] >= 65 && str[i] <= 90){
            str[i] = str[i] + 32;
        }
        i++;
    }
    return str;
}
