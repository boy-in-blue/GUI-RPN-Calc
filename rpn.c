#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <limits.h>
#include <SDL.h>
#include <SDL_timer.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "stack.h"
#include "mylib.h"

#define STACK_SIZE 5

int unmain(int argc, char *argv[])
{
    struct Stack *stack = create_stack(STACK_SIZE);

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
            operator= string_to_operator(input);
            if (operator!= '\0')
            {
                if (get_top(stack) < 1)
                {
                    printf("Not enought elements on the stack\n");
                }
                else
                {
                    int a = pop(stack);
                    int b = pop(stack);
                    if (a == 0 && operator== '/')
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

int create_number_realtime(int old, int new)
{
    if (old == 0)
        return new;
    int n = 0;
    int rv = 0;
    int copyold = old;
    int count = 0;
    while (copyold != 0)
    {
        copyold /= 10;
        ++count;
    }
    copyold = old;
    for (count = count - 1; count >= 0; count--)
    {
        n = copyold / (int)pow(10, count);
        copyold = copyold - n * (int)pow(10, count);
        rv += n * (int)pow(10, count + 1);
    }
    rv += new;
    return rv;
}

void operate_stack(struct Stack *s, char operator)
{
    if (get_top(s) < 1)
    {
        printf("Not enought elements on the stack\n");
    }
    else
    {
        int a = pop(s);
        int b = pop(s);
        if (a == 0 && operator== '/')
        {
            dividebyzero();
        }
        else
        {
            push(s, operate(b, a, operator));
        }
    }
}

int main(int argc, char *args[])
{
    struct Stack *stack = create_stack(STACK_SIZE);

    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        printf("error initializing SDL: %s\n", SDL_GetError());
        return 1;
    }

    if (TTF_Init() != 0)
    {
        printf("error initializing ttf: %s\n", TTF_GetError());
        SDL_Quit();
        return 1;
    }

    TTF_Font *font = TTF_OpenFont("./font/OpenSans-ExtraBold.ttf", 72);

    if (!font)
    {
        printf("font opening failed: %s\n", TTF_GetError());
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    SDL_Window *win = SDL_CreateWindow("RPN Calc",
                                       SDL_WINDOWPOS_CENTERED,
                                       SDL_WINDOWPOS_CENTERED,
                                       400, 1000, 0);
    if (!win)
    {
        printf("error creating window: %s\n", SDL_GetError());
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    Uint32 render_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
    SDL_Renderer *rend = SDL_CreateRenderer(win, -1, render_flags);
    if (!rend)
    {
        printf("error creating renderer: %s\n", SDL_GetError());
        TTF_Quit();
        SDL_DestroyWindow(win);
        SDL_Quit();
        return 1;
    }

    SDL_Surface *surface = IMG_Load("./gfx/generate.png");
    if (!surface)
    {
        printf("error creating surface\n");
        TTF_Quit();
        SDL_DestroyRenderer(rend);
        SDL_DestroyWindow(win);
        SDL_Quit();
        return 1;
    }

    SDL_Color color = {0, 0, 0};

    SDL_Texture *tex = SDL_CreateTextureFromSurface(rend, surface);
    SDL_FreeSurface(surface);
    if (!tex)
    {
        printf("error creating texture: %s\n", SDL_GetError());
        SDL_DestroyRenderer(rend);
        SDL_DestroyWindow(win);
        SDL_Quit();
        return 1;
    }
    char buffer[STACK_SIZE][16];
    int z = 30123;

    SDL_Surface *text_surface; // = TTF_RenderText_Solid(font, buffer, color);

    SDL_Texture *text; // = SDL_CreateTextureFromSurface(rend, text_surface);

    // SDL_FreeSurface(text_surface);

    // if (!text)
    // {
    //     printf("error creating texture: %s\n", SDL_GetError());
    //     SDL_DestroyRenderer(rend);
    //     SDL_DestroyWindow(win);
    //     SDL_Quit();
    //     return 1;
    // }

    SDL_Rect text_rect = {111, 0};
    SDL_QueryTexture(text, NULL, NULL, &text_rect.w, &text_rect.h);

    int *arr = get_all_values(stack);

    int input = 0;
    int full_input = 0;
    int close_requested = 0;
    while (!close_requested)
    {
        arr = get_all_values(stack);
        for (int i = 0; i < STACK_SIZE; i++)
        {
            sprintf(buffer[i], "%d", arr[i]);
        }
        SDL_RenderClear(rend);
        SDL_RenderCopy(rend, tex, NULL, NULL);

        for (int i = 0; i < 5; i++)
        {
            text_surface = TTF_RenderText_Solid(font, buffer[i], color);
            text_rect.x = 111;
            text_rect.y = 100 * i;
            SDL_QueryTexture(text, NULL, NULL, &text_rect.w, &text_rect.h);
            text = SDL_CreateTextureFromSurface(rend, text_surface);
            SDL_FreeSurface(text_surface);
            SDL_RenderCopy(rend, text, NULL, &text_rect);
        }
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                close_requested = 1;
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.scancode)
                {
                case SDL_SCANCODE_KP_0:
                case SDL_SCANCODE_0:
                    input = 0;
                    full_input = create_number_realtime(full_input, input);
                    break;
                case SDL_SCANCODE_KP_1:
                case SDL_SCANCODE_1:
                    input = 1;
                    full_input = create_number_realtime(full_input, input);
                    break;
                case SDL_SCANCODE_KP_2:
                case SDL_SCANCODE_2:
                    input = 2;
                    full_input = create_number_realtime(full_input, input);
                    break;
                case SDL_SCANCODE_KP_3:
                case SDL_SCANCODE_3:
                    input = 3;
                    full_input = create_number_realtime(full_input, input);
                    break;
                case SDL_SCANCODE_KP_4:
                case SDL_SCANCODE_4:
                    input = 4;
                    full_input = create_number_realtime(full_input, input);
                    break;
                case SDL_SCANCODE_KP_5:
                case SDL_SCANCODE_5:
                    input = 5;
                    full_input = create_number_realtime(full_input, input);
                    break;
                case SDL_SCANCODE_KP_6:
                case SDL_SCANCODE_6:
                    input = 6;
                    full_input = create_number_realtime(full_input, input);
                    break;
                case SDL_SCANCODE_KP_7:
                case SDL_SCANCODE_7:
                    input = 7;
                    full_input = create_number_realtime(full_input, input);
                    break;
                case SDL_SCANCODE_KP_8:
                case SDL_SCANCODE_8:
                    input = 8;
                    full_input = create_number_realtime(full_input, input);
                    break;
                case SDL_SCANCODE_KP_9:
                case SDL_SCANCODE_9:
                    input = 9;
                    full_input = create_number_realtime(full_input, input);
                    break;
                case SDL_SCANCODE_KP_PLUS:
                    operate_stack(stack, '+');
                    break;
                case SDL_SCANCODE_KP_MINUS:
                    operate_stack(stack, '-');
                    break;
                case SDL_SCANCODE_KP_MULTIPLY:
                    operate_stack(stack, '*');
                    break;
                case SDL_SCANCODE_KP_DIVIDE:
                    operate_stack(stack, '/');
                    break;

                case SDL_SCANCODE_RETURN:
                case SDL_SCANCODE_KP_ENTER:
                    push(stack, full_input);
                    full_input = 0;
                default:
                    break;
                }
                break;
            }
        }

        SDL_RenderPresent(rend);

        SDL_Delay(1000 / 60);
    }
    SDL_FreeSurface(text_surface);
    SDL_DestroyTexture(tex);
    SDL_DestroyTexture(text);
    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}
