#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <SDL.h>
#include <SDL_timer.h>
#include <SDL_image.h>
#include "stack.h"
#include "mylib.h"

#define STACK_SIZE 10

int unmain(int argc, char *argv[])
{
    struct Stack* stack = create_stack(STACK_SIZE);

    // take inputs
    char input[16] = {'\0'};
    scanf("%s", input);
    int input_int;
    char operator;
    while (strcmp(input, "exit") != 0)
    {
        input_int = string_to_int(input);
        if (input_int == INT_MIN)
        {
            operator = string_to_operator(input);
            if (operator != '\0')
            {
                if (get_top(stack) < 1)
                {
                    printf("Not enought elements on the stack\n");
                }
                else
                {
                    int a = pop(stack);
                    int b = pop(stack);
                    if (a == 0 && operator == '/')
                    {
                        dividebyzero();
                        exit(1);
                    }
                    else
                    {
                        push(stack, operate(b, a, operator));
                    }
                }
            }
            else
            {
                printf("Not valid input\n");
            }
        }
        else
        {
            push(stack, input_int);
        }
        scanf("%s", input);
    }

    return 0;
}

int main(int argc, char *args[])
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        printf("error initializing SDL: %s\n", SDL_GetError());
        return 1;
    }
    SDL_Window* win = SDL_CreateWindow("RPN Calc",
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            400, 800, 0);
    if (!win)
    {
        printf("error creating window: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    Uint32 render_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
    SDL_Renderer* rend = SDL_CreateRenderer(win, -1, render_flags);
    if (!rend)
    {
        printf("error creating renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(win);
        SDL_Quit();
        return 1;
    }

    SDL_Surface* surface = IMG_Load("./gfx/calc.png");
    if (!surface)
    {
        printf("error creating surface\n");
        SDL_DestroyRenderer(rend);
        SDL_DestroyWindow(win);
        SDL_Quit();
        return 1;
    }

    SDL_Texture* tex = SDL_CreateTextureFromSurface(rend, surface);
    SDL_FreeSurface(surface);
    if (!surface)
    {
        printf("error creating texture: %s\n", SDL_GetError());
        SDL_DestroyRenderer(rend);
        SDL_DestroyWindow(win);
        SDL_Quit();
        return 1;
    }
    
    SDL_RenderClear(rend);
    SDL_RenderCopy(rend, tex, NULL, NULL);
    SDL_RenderPresent(rend);

    SDL_Delay(5000);

    SDL_DestroyTexture(tex);
    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;

}

