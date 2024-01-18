/*
    CRender - 1.0 - alpha 
    Creator - Grathrram
    Created - 18.01.2024
*/

#include "CRenderEx.h"
#include <time.h>

#define ResolutionX 80
#define ResolutionY 30

#ifdef WIN32
#include <windows.h>
#define sleep Sleep(100)
#else
#include <unistd.h>
#define sleep usleep(100 * 1000)
#endif


int main(void) {
    srand(time(NULL));
    CR_CRender Render;
    CR_InitCRender(&Render, ResolutionX , ResolutionY);
    Render.Filler = ' ';
    CR_CRenderFill(&Render, (CR_Color){0,0,0});

    CR_Rect Rect = {0};
    Rect.Color = (CR_Color){0,0,255};
    Rect.Height = ResolutionY;
    Rect.Width  = 0;

    CR_Rect Rect2 = {0};
    Rect2.Color = (CR_Color){0,0,0};
    Rect2.Height = ResolutionY;
    Rect2.Width = 0;

    while(1) {
        for(uint32_t i = ResolutionX; i != 0; --i) {
            CR_Rect2CRender(&Render, Rect);
            CR_Rect2CRender(&Render, Rect2);
            Rect2.Width = i - 1; 
            Rect.Width = i;
            Rect.Color = (CR_Color){rand() % 255,rand() % 255,rand() % 255};
            CR_ConsoleClear;
            CR_CRenderPrint(Render, CR_Color_BackG);
            sleep;
        }
    }
    

    CR_CRenderPrint(Render, CR_Color_BackG);


    return 0;
}