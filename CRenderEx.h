/*
    CRenderEx - 1.0v
    Creator: Grathrram
    start of dev: 27.01.2024
    License GNU GPL 3
*/

#ifndef CRENDEREX_H
#define CRENDEREX_H

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define SIGNONE 0 //no error
#define SIGOUTM 1 //out of memory
//#define SIGOUTB 2 //out of borders not used
#define SIGINPE 3 //Input Error

#ifdef WIN32
#include <windows.h>
#define CR_ConsoleClear system("cls")
#else
#include <unistd.h>
#define CR_ConsoleClear system("clear")
#endif

//no BackGround
#define CR_ColorMode_Text       38
#define CR_ColorMode_Background 48

typedef struct CR_Color {
    uint8_t Red;
    uint8_t Green;
    uint8_t Blue;
    uint8_t Alpha;
    uint8_t draw;
} CR_Color;

typedef struct CR_Render {
    CR_Color **Pixel;
    char **Chars;
    uint32_t ResolutionX;
    uint32_t ResolutionY;
} CR_Render;

typedef struct CR_Rect {
    uint32_t x;
    uint32_t y;
    uint32_t Width;
    uint32_t Height;
    char Char;
    CR_Color Color;
} CR_Rect;
//If No Errors Returns 0 Else errsig (All Functions!!! if not void)
//If you see any error please fix or report. Thanks!!!

uint8_t CR_InitRender(CR_Render *Render, uint32_t ResolutionX, uint32_t ResolutionY); //Sets Resolution of Render and allocs space
void CR_DestroyRender(CR_Render Render);//Frees Render (After that you can Init Another Render)

void CR_RenderFill (CR_Render *Render, char Character, CR_Color Color); //Fills Render With Color
void CR_RenderPrint(CR_Render Render, uint8_t backGround); //Prints Graphics/Display You know what i mean

void CR_RenderSetPixel(CR_Render *Render, uint32_t PositionX, uint32_t PositionY, char Character, CR_Color Color);//Replace Character at given position
void CR_RenderDrawLine(CR_Render *Render, uint32_t StartX, uint32_t StartY, uint32_t EndX, uint32_t EndY, char Character, CR_Color Color);//Draws a line
void CR_RenderDrawRect(CR_Render *Render, uint32_t x, uint32_t y, uint32_t w, uint32_t h, char Char, CR_Color Color);//Overwrites render with rect
void CR_RenderDrawText(CR_Render *Render, uint32_t x, uint32_t y, uint32_t MaxWidth, uint32_t MaxHeight, const char* Text, CR_Color Color);//draws Text in render

void CR_Rect2Render(CR_Render *Render, CR_Rect Rect);//Overwrites render with rect

//calculates Transparency
CR_Color CR_ApplayAlpha(CR_Color Curent, CR_Color Background);

void CR_GetErrDesc(uint8_t Error); //prints description of error

#endif //!CRENDEREX_H
