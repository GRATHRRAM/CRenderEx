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
    char Fill;
} CR_Rect;

//If No Errors Returns 0 Else errsig (All Functions!!! if not void)
int CR_AllocRender  (CR_Render *Render, uint32_t ResolutionX, uint32_t ResolutionY); //Allocs space on heap for Render
int CR_ReallocRender(CR_Render *Render, uint32_t ResolutionX, uint32_t ResolutionY); //Changes Resolution For Already Existing Render

void CR_RenderFill (CR_Render *Render, char Character); //Fills Render With Characters
void CR_RenderPrint(CR_Render Render);                  //Prints Graphics/Display You know what i mean


//If you see any error please fix or report. Thanks!!!
int CR_AllocRender(CR_Render *Render, uint32_t ResolutionX, uint32_t ResolutionY) {
    Render->Chars = (char**) malloc(sizeof(char*) * ResolutionY);
    for(uint32_t i=0; i < ResolutionY; ++i)
        Render->Chars[i] = (char*) malloc(sizeof(char) * ResolutionX);
    
    if(Render->Chars == NULL) return 1;
    else {
        Render->ResolutionX = ResolutionX;
        Render->ResolutionY = ResolutionY;
    }
    return 0;
}

int CR_ReallocRender(CR_Render *Render, uint32_t ResolutionX, uint32_t ResolutionY) {
    Render->Chars = (char**) realloc(Render->Chars ,sizeof(char*) * ResolutionY);
    for(uint32_t i=0; i < ResolutionY; ++i)
        Render->Chars[i] = (char*) realloc(Render->Chars ,sizeof(char) * ResolutionX);
    
    if(Render->Chars == NULL) return 1;
    else {
        Render->ResolutionX = ResolutionX;
        Render->ResolutionY = ResolutionY;
    }
    return 0;
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

#endif //!CRENDEREX_H