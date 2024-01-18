#include "CRenderEx.h"
#include <time.h>

#define ResolutionX 80
#define ResolutionY 25


int main(void) {
    srand(time(NULL));
    CR_CRender Render;
    CR_InitCRender(&Render, ResolutionX , ResolutionY);
    Render.Filler = ' ';
    CR_CRenderFill(&Render, (CR_Color){255,0,0});

    CR_Rect Rect = {0};
    Rect.Color = (CR_Color){0,0,255};
    Rect.Height = ResolutionY;
    Rect.Width  = ResolutionX;

    while(1) {
        CR_Rect2CRender(&Render, Rect);
        Rect.Height--;
        Rect.Width--;
        Rect.Color = (CR_Color){rand() % 255,rand() % 255,rand() % 255};
        CR_ConsoleClear;
        CR_CRenderPrint(Render, CR_Color_BackG);
    }
    

    CR_CRenderPrint(Render, CR_Color_BackG);


    return 0;
}