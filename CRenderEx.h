/*
    CRenderEx - 0.50v
    Creator: Grathrram
    start of dev: 12.01.2024
    License GNU GPL 3
*/

#ifndef CRENDEREX_H
#define CRENDEREX_H

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#define SIGNONE 0 //no error
#define SIGOUTM 1 //out of memory
#define SIGOUTB 2 //out of borders
#define SIGINPE 3 //Input Error

#ifdef WIN32
#include <windows.h>
#define CR_ConsoleClear system("cls")
#else
#include <unistd.h>
#define CR_ConsoleClear system("clear")
#endif

typedef struct  CR_Render {
    char **Chars;
    uint32_t ResolutionX;
    uint32_t ResolutionY;
} CR_Render;

typedef struct CR_Rect {
    uint32_t x;
    uint32_t y;
    uint32_t Height;
    uint32_t Width;
    char Char;
} CR_Rect;

//If No Errors Returns 0 Else errsig (All Functions!!! if not void)
//If you see any error please fix or report. Thanks!!!
uint8_t CR_AllocRender  (CR_Render *Render, uint32_t ResolutionX, uint32_t ResolutionY); //Allocs space on heap for Render
uint8_t CR_ReallocRender(CR_Render *Render, uint32_t ResolutionX, uint32_t ResolutionY); //Changes Resolution For Already Existing Render

void CR_RenderFill (CR_Render *Render, char Character); //Fills Render With Characters
void CR_RenderPrint(CR_Render Render);                  //Prints Graphics/Display You know what i mean

uint8_t CR_RenderSetChar(CR_Render *Render, uint32_t PositionX, uint32_t PositionY,  char Character);//Replace Character at given position
uint8_t CR_RenderDrawLine(CR_Render *Render, uint32_t StartX, uint32_t StartY, uint32_t EndX, uint32_t EndY, char Character);//Draws a line

uint8_t CR_Rect2Render(CR_Render *Render, CR_Rect Rect);//Overwrites render with rect

void CR_GetErrDesc(uint8_t Error); //prints description of error


uint8_t CR_AllocRender(CR_Render *Render, uint32_t ResolutionX, uint32_t ResolutionY) {
    Render->Chars = (char**) malloc(sizeof(char*) * ResolutionY);
    for(uint32_t i=0; i < ResolutionY; ++i)
        Render->Chars[i] = (char*) malloc(sizeof(char) * (ResolutionX + 1));
    
    if(Render->Chars == NULL) return SIGOUTM;
    else {
        Render->ResolutionX = ResolutionX;
        Render->ResolutionY = ResolutionY;
    }
    return SIGNONE;
}

uint8_t CR_ReallocRender(CR_Render *Render, uint32_t ResolutionX, uint32_t ResolutionY) {
    Render->Chars = (char**) realloc(Render->Chars ,sizeof(char*) * ResolutionY);
    for(uint32_t i=0; i < ResolutionY; ++i)
        Render->Chars[i] = (char*) realloc(Render->Chars ,sizeof(char) * (ResolutionX + 1));
    
    if(Render->Chars == NULL) return SIGOUTM;
    else {
        Render->ResolutionX = ResolutionX;
        Render->ResolutionY = ResolutionY;
    }
    return SIGNONE;
}

void CR_RenderFill(CR_Render *Render, char Character) {
    for(uint32_t y=0; y < Render->ResolutionY; ++y) {
        for(uint32_t x=0; x < Render->ResolutionX; ++x) {
            Render->Chars[y][x] = Character;
        }
    }
}

void CR_RenderPrint(CR_Render Render) {
    for(uint32_t y=0; y < Render.ResolutionY; ++y) {
        puts(Render.Chars[y]);
    }
}

uint8_t CR_RenderSetChar(CR_Render *Render, uint32_t PositionX, uint32_t PositionY, char Character) {
    if(Render->ResolutionX < PositionX ||
       Render->ResolutionY <= PositionY)
        return SIGOUTB;
    else Render->Chars[PositionY][PositionX] = Character;
    return SIGNONE;
}

uint8_t CR_RenderDrawLine(CR_Render *Render, uint32_t StartX, uint32_t StartY,
uint32_t EndX, uint32_t EndY, char Character) {
    uint32_t x, y, dx, dy, dx1, dy1, px, py, xe, ye, i;  
    dx = EndX - StartX;
    dy = EndY - StartY;   
    dx1 = abs(dx);
    dy1 = abs(dy); 
    px = 2 * dy1 - dx1;
    py = 2 * dx1 - dy1;  
    if (dy1 <= dx1) {    
        if (dx >= 0) {
            x = StartX; y = StartY; xe = EndX;
        } else {
            x = EndX; y = EndY; xe = StartX;
        }        CR_RenderSetChar(Render, x , y, Character);
        for (i = 0; x < xe; i++) {
            x = x + 1;    
            if (px < 0) {
                px = px + 2 * dy1;
            } else {
                if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0)) {
                    y = y + 1;
                } else {
                    y = y - 1;
                }
                px = px + 2 * (dy1 - dx1);
            }      
            CR_RenderSetChar(Render, x , y, Character);
        }    } else {
        if (dy >= 0) {
            x = StartX; y = StartY; ye = EndY;
        } else {
            x = EndX; y = EndY; ye = StartY;
        }        CR_RenderSetChar(Render, x , y, Character);
        for (i = 0; y < ye; i++) {
            y = y + 1;            
            if (py <= 0) {
                py = py + 2 * dx1;
            } else {
                if ((dx < 0 && dy<0) || (dx > 0 && dy > 0)) {
                    x = x + 1;
                } else {
                    x = x - 1;
                }
                py = py + 2 * (dx1 - dy1);
            }            
            CR_RenderSetChar(Render, x , y, Character);
        }
    }
}

uint8_t CR_Rect2Render(CR_Render *Render, CR_Rect Rect) {
    uint8_t rval = 0;
    for(uint32_t y = Rect.y; y - Rect.y < Rect.Height; ++y) {
        for(uint32_t x = Rect.x; x - Rect.x < Rect.Width; ++x) {
           rval = CR_RenderSetChar(Render, x, y, Rect.Char);
        }
    }
    return rval;
}

void CR_GetErrDesc(uint8_t Error) {
    if(Error == 0) printf("CRender-> No Error. Youre Good!\n");                                     //SIGNONE 
    if(Error == 1) printf("CRender-> Out Of Memory. Error Occurs Mostly When Allocating Render\n"); //SIGOUTM
    if(Error == 2) printf("CRender-> Out Of Borders. (Warning) You haved tryed to do some thing out of render Borders\n"); //SIGOUTM
    if(Error == 3) printf("CRender-> Input Error. Cant Get Input."); //SIGINPE
    else printf("CRender-> Error Not Exist. Error Signal not Exitst!\n");
}

#endif //!CRENDEREX_H