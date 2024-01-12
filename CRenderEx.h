/*
    CRenderEx - 0.25v
    Creator: Grathrram
    start of dev: 11.01.2024
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
       Render->ResolutionY < PositionY)
        return SIGOUTB;
    else Render->Chars[PositionY][PositionX] = Character;
    return SIGNONE;
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
    else printf("CRender-> Error Not Exist. Error Signal not Exitst! What did you do?\n");
}

#endif //!CRENDEREX_H