#include <math.h>
#include <string.h>
#include <limits.h>
#include <stdio.h>
#include "mylib.h"

int string_to_int(char const *c)
{
    int i = 0, j = 0;
    int number = 0;
    int max_int[11];
    while (c[i] != '\0')
    {
        if (c[i] > 47 && c[i] < 58)
        {
            max_int[i] = (c[i] - 48) % 10;
        }
        else
        {
            return INT_MIN;
        }
        i++;
    }
    max_int[i] = -1;
    i--;
    while (i > -1)
    {
        number += max_int[i] * (pow(10, j));
        i--;
        j++;
    }
    return number;
}

char string_to_operator(char const *c)
{
    switch(c[0])
    {
        case 43:
            return '+';
        case 45:
            return '-';
        case 42:
            return '*';
        case 47:
            return '/';
        default:
            return '\0';
    }
}

int operate(int a, int b, char op)
{
    switch(op)
    {
        case '+':
            return a+b;
        case '-':
            return a-b;
        case '*':
            return a*b;
        case '/':
            return a/b;
        default:
            return INT_MIN;
    }
}

void dividebyzero()
{
pyprintfr("     _.-^^---....,,--        \n");
pyprintfr(" _--                  --_    \n");
pyprintfr("<                        >)  \n");
pyprintfr("|                         |  \n");
pyprintfr(" \\._                   _./   \n");
pyprintfr("    ```--. . , ; .--'''      \n");
pyprintfr("          | |   |            \n");
pyprintfr("       .-=||  | |=-.         \n");
pyprintfr("       `-=#$%&%$#=-'         \n");
pyprintfr("          | ;  :|            \n");
pyprintfr(" _____.,-#%&$@%#&#~,._____   \n");
printf("         DIVISION\n");
printf("            BY\n");
printf("           ZERO\n");
}

void pyprintfr(char* r)
{
    for(int i=0; i<strlen(r); i++)
    {
        printf("%c", r[i]);
    }
    printf("\n");
}


