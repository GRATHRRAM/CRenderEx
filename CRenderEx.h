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
#include <stdbool.h>

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

//#define CR_ColorName (CR_Color){Red,Green,Blue,Alpha,Draw?}
#define CR_FRED   (CR_Color){255,0,0,255,true} //Full Red
#define CR_FGREEN (CR_Color){0,255,0,255,true} //Full Green
#define CR_FBLUE  (CR_Color){0,0,255,255,true} //Full Blue

#define CR_WHITE (CR_Color){255,255,255,255,true} //White
#define CR_BLACK (CR_Color){0,0,0,255,true}   //Black
#define CR_VOID  (CR_Color){0,0,0,0,false}    //Its fully Transparent and its not drawn

#define CRC_LIGHTGRAY  (CR_Color){ 200, 200, 200, 255, true}   // Light Gray
#define CRC_GRAY       (CR_Color){ 130, 130, 130, 255, true}   // Gray
#define CRC_DARKGRAY   (CR_Color){ 80, 80, 80, 255, true}      // Dark Gray
#define CRC_YELLOW     (CR_Color){ 253, 249, 0, 255, true}     // Yellow
#define CRC_GOLD       (CR_Color){ 255, 203, 0, 255, true}     // Gold
#define CRC_ORANGE     (CR_Color){ 255, 161, 0, 255, true}     // Orange
#define CRC_PINK       (CR_Color){ 255, 109, 194, 255, true}   // Pink
#define CRC_RED        (CR_Color){ 230, 41, 55, 255, true}     // Red
#define CRC_MAROON     (CR_Color){ 190, 33, 55, 255, true}     // Maroon
#define CRC_GREEN      (CR_Color){ 0, 228, 48, 255, true}      // Green
#define CRC_LIME       (CR_Color){ 0, 158, 47, 255, true}      // Lime
#define CRC_DARKGREEN  (CR_Color){ 0, 117, 44, 255, true}      // Dark Green
#define CRC_SKYBLUE    (CR_Color){ 102, 191, 255, 255, true}   // Sky Blue
#define CRC_BLUE       (CR_Color){ 0, 121, 241, 255, true}     // Blue
#define CRC_DARKBLUE   (CR_Color){ 0, 82, 172, 255, true}      // Dark Blue
#define CRC_PURPLE     (CR_Color){ 200, 122, 255, 255, true}   // Purple
#define CRC_VIOLET     (CR_Color){ 135, 60, 190, 255, true}    // Violet
#define CRC_DARKPURPLE (CR_Color){ 112, 31, 126, 255, true}    // Dark Purple
#define CRC_BEIGE      (CR_Color){ 211, 176, 131, 255, true}   // Beige
#define CRC_BROWN      (CR_Color){ 127, 106, 79, 255, true}    // Brown
#define CRC_DARKBROWN  (CR_Color){ 76, 63, 47, 255, true}      // Dark Brown
#define CRC_MAGENTA    (CR_Color){ 255, 0, 255, 255, true}     // Magenta

typedef struct CR_Color {
    uint8_t Red;
    uint8_t Green;
    uint8_t Blue;
    uint8_t Alpha;
    bool draw;
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

typedef struct CR_Texture {
    char **Chars;
    CR_Color **Pixel;
    uint32_t Height;
    uint32_t Width;
} CR_Texture;
//If No Errors Returns 0 Else errsig (All Functions!!! if not void)
//If you see any error please fix or report. Thanks!!!

uint8_t CR_InitRender(CR_Render *Render, uint32_t ResolutionX, uint32_t ResolutionY); //Sets Resolution of Render and allocs space
void CR_DestroyRender(CR_Render *Render);//Frees Render (After that you can Init Another Render)

void CR_RenderFill (CR_Render *Render, char Character, CR_Color Color); //Fills Render With Color
void CR_RenderPrint(CR_Render *Render, uint8_t backGround); //Prints Graphics/Display You know what i mean

void CR_RenderSetPixel(CR_Render *Render, uint32_t PositionX, uint32_t PositionY, char Character, CR_Color Color);//Replace Character at given position
void CR_RenderDrawLine(CR_Render *Render, uint32_t StartX, uint32_t StartY, uint32_t EndX, uint32_t EndY, char Character, CR_Color Color);//Draws a line
void CR_RenderDrawRect(CR_Render *Render, uint32_t x, uint32_t y, uint32_t h, uint32_t w, char Char, CR_Color Color);//Draws Only outlines of Rect
void CR_RenderDrawRectNP(CR_Render *Render, uint32_t x, uint32_t y, uint32_t w, uint32_t h, char Char, CR_Color Color);//Draws Rect With Normal Proporcion
void CR_RenderDrawRectFill(CR_Render *Render, uint32_t x, uint32_t y, uint32_t w, uint32_t h, char Char, CR_Color Color);//Overwrites render with rect
void CR_RenderDrawText(CR_Render *Render, uint32_t x, uint32_t y, uint32_t MaxWidth, uint32_t MaxHeight, const char* Text, CR_Color Color);//draws Text in render
void CR_RenderDrawCircle(CR_Render *Render ,int x, int y, int Radius, char Char, CR_Color Color);//Draws only outlines of circle
void CR_RenderDrawCircleFill(CR_Render *Render, int x, int y, int Radius, char Char, CR_Color Color);//Draws Circle And fills it
void CR_RenderDrawEllipse(CR_Render *Render, int x, int y, int w, int h, char Char, CR_Color Color);//Draws only outlines of Elipse
void CR_RenderDrawEllipseFill(CR_Render *Render, int x, int y, int w, int h, char Char, CR_Color Color);//Draws elipse and fills it

void CR_Rect2Render(CR_Render *Render, CR_Rect Rect);//Overwrites render with rect

CR_Color CR_ApplayAlpha(CR_Color Curent, CR_Color Background);//calculates Transparency

bool CR_ColisionRect(uint32_t x1 , uint32_t y1, uint32_t w1, uint32_t h1, uint32_t x2 , uint32_t y2, uint32_t w2, uint32_t h2);
bool CR_ColisionElipse(uint32_t x1 , uint32_t y1, uint32_t w1, uint32_t h1, uint32_t x2 , uint32_t y2, uint32_t w2, uint32_t h2);

void CR_GetErrDesc(uint8_t Error); //prints description of error

#endif //!CRENDEREX_H
