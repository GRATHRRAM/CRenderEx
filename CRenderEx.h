/*
    CRenderEx - 1.5v
    Creator: Grathrram
    start of dev: 12.04.2024
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

//#define CRC_ColorName (CR_Color){Red,Green,Blue,Alpha} CRC = ConsolerRenderColor
#define CRC_FRED   (CR_Color){255,0,0,255} //Full Red
#define CRC_FGREEN (CR_Color){0,255,0,255} //Full Green
#define CRC_FBLUE  (CR_Color){0,0,255,255} //Full Blue

#define CRC_WHITE (CR_Color){255,255,255,255} //White
#define CRC_BLACK (CR_Color){0,0,0,255}       //Black
#define CRC_VOID  (CR_Color){0,0,0,0}         //Its fully Transparent

#define CRC_LIGHTGRAY  (CR_Color){ 200, 200, 200, 255}   // Light Gray
#define CRC_GRAY       (CR_Color){ 130, 130, 130, 255}   // Gray
#define CRC_DARKGRAY   (CR_Color){ 80, 80, 80, 255}      // Dark Gray
#define CRC_YELLOW     (CR_Color){ 253, 249, 0, 255}     // Yellow
#define CRC_GOLD       (CR_Color){ 255, 203, 0, 255}     // Gold
#define CRC_ORANGE     (CR_Color){ 255, 161, 0, 255}     // Orange
#define CRC_PINK       (CR_Color){ 255, 109, 194, 255}   // Pink
#define CRC_RED        (CR_Color){ 230, 41, 55, 255}     // Red
#define CRC_MAROON     (CR_Color){ 190, 33, 55, 255}     // Maroon
#define CRC_GREEN      (CR_Color){ 0, 228, 48, 255}      // Green
#define CRC_LIME       (CR_Color){ 0, 158, 47, 255}      // Lime
#define CRC_DARKGREEN  (CR_Color){ 0, 117, 44, 255}      // Dark Green
#define CRC_SKYBLUE    (CR_Color){ 102, 191, 255, 255}   // Sky Blue
#define CRC_BLUE       (CR_Color){ 0, 121, 241, 255}     // Blue
#define CRC_DARKBLUE   (CR_Color){ 0, 82, 172, 255}      // Dark Blue
#define CRC_PURPLE     (CR_Color){ 200, 122, 255, 255}   // Purple
#define CRC_VIOLET     (CR_Color){ 135, 60, 190, 255}    // Violet
#define CRC_DARKPURPLE (CR_Color){ 112, 31, 126, 255}    // Dark Purple
#define CRC_BEIGE      (CR_Color){ 211, 176, 131, 255}   // Beige
#define CRC_BROWN      (CR_Color){ 127, 106, 79, 255}    // Brown
#define CRC_DARKBROWN  (CR_Color){ 76, 63, 47, 255}      // Dark Brown
#define CRC_MAGENTA    (CR_Color){ 255, 0, 255, 255}     // Magenta

#define Vector2_Zero (Vector2){0}
#define Vector2i_Zero (Vector2i){0}  

typedef struct CR_Color {
    uint8_t r;//Red;
    uint8_t g;//Green;
    uint8_t b;//Blue;
    uint8_t a;//Alpha;
} CR_Color;

typedef struct CR_Render {
    CR_Color **Pixel;
    char **Chars;
    uint32_t ResolutionX;
    uint32_t ResolutionY;
} CR_Render;

typedef struct Vector2 {
  float x;
  float y;
} Vector2;

typedef struct Vector2i {
    int x;
    int y;
} Vector2i;

typedef struct CR_Rect {
    int32_t x;
    int32_t y;
    int32_t w; //Width
    int32_t h; //Height
} CR_Rect;

//If No Errors Returns 0 Else errsig (All Functions!!! if not void)
//If you see any bug please fix or report. Thanks!!!

uint8_t CR_InitRender(CR_Render *Render, uint32_t ResolutionX, uint32_t ResolutionY); //Sets Resolution of Render and allocs space
void CR_DestroyRender(CR_Render *Render);//Frees Render (After that you can Init Another Render)

void CR_RenderFill (CR_Render *Render, char Character, CR_Color Color); //Fills Render With Color
void CR_RenderPrint(CR_Render *Render, uint8_t backGround, Vector2i SizeofPrint); //Prints Graphics/Display You know what i mean
void CR_RenderStretch(CR_Render *Render);//from 1:1 to 2:1 (normal proporcions for color rendering use text after stretch)

void CR_RenderSetPixel(CR_Render *Render, int32_t PositionX, int32_t PositionY, char Character, CR_Color Color);//Replace Character at given position
void CR_RenderDrawLine(CR_Render *Render, char Character,CR_Color Color, int32_t StartX, int32_t StartY, int32_t EndX, int32_t EndY);//Draws a line
void CR_RenderDrawRect(CR_Render *Render, int32_t x, int32_t y, int32_t h, int32_t w, char Char, CR_Color Color);//Draws Only outlines of Rect
void CR_RenderDrawRectNP(CR_Render *Render, int32_t x, int32_t y, int32_t w, int32_t h, char Char, CR_Color Color);//Draws Rect With Normal Proporcion
void CR_RenderDrawRectFill(CR_Render *Render, int32_t x, int32_t y, int32_t w, int32_t h, char Char, CR_Color Color);//draws a rect
void CR_RenderDrawText(CR_Render *Render, int32_t x, int32_t y, int32_t MaxWidth, int32_t MaxHeight, const char* Text, CR_Color Color);//draws Text in render
void CR_RenderDrawCircle(CR_Render *Render ,int x, int y, int Radius, char Char, CR_Color Color);//Draws only outlines of circle
void CR_RenderDrawCircleFill(CR_Render *Render, int x, int y, int Radius, char Char, CR_Color Color);//Draws Circle And fills it
void CR_RenderDrawEllipse(CR_Render *Render, int x, int y, int w, int h, char Char, CR_Color Color);//Draws only outlines of Elipse
void CR_RenderDrawEllipseFill(CR_Render *Render, int x, int y, int w, int h, char Char, CR_Color Color);//Draws elipse and fills it

void CR_Rect2Render(CR_Render *Render, CR_Rect Rect, char Character, CR_Color Color);//draws a rect

CR_Color CR_ApplayAlpha(CR_Color Curent, CR_Color Background);//calculates Transparency

bool CR_ColisionRect(int32_t x1 , int32_t y1, int32_t w1, int32_t h1, int32_t x2 , int32_t y2, int32_t w2, int32_t h2);
bool CR_ColisionRectSH(CR_Rect Rect1, CR_Rect Rect2);
bool CR_ColisionElipse(int32_t x1 , int32_t y1, int32_t w1, int32_t h1, int32_t x2 , int32_t y2, int32_t w2, int32_t h2);

void CR_GetErrDesc(uint8_t Error); //prints description of error

float CR_Math_Deg2Rad(float Deg);
float CR_Math_Rad2Deg(float Rad);
Vector2 CR_Math_RotateLine(Vector2 Start, Vector2 End, float RadAngle);
#endif //!CRENDEREX_H
