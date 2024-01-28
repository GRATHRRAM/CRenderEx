/*
    CRender - 1.0
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
    CR_Render Render;
    CR_InitRender(&Render, ResolutionX , ResolutionY);
    CR_RenderFill(&Render, ' ', (CR_Color){0,0,0,255,1});

    CR_Rect Rect = {0};
    Rect.Char = ' ';
    Rect.Color = (CR_Color){0,0,255,255,1};
    Rect.Height = ResolutionY;
    Rect.Width  = 0;

    CR_Rect Rect2 = {0};
    Rect.Char = ' ';
    Rect2.Color = (CR_Color){0,0,0, 255,1};
    Rect2.Height = ResolutionY;
    Rect2.Width = 0;

    while(1) {
        for(uint32_t i = ResolutionX; i != 0; --i) {
            CR_Rect2Render(&Render, Rect);
            CR_Rect2Render(&Render, Rect2);
            Rect2.Width = i - 1; 
            Rect.Width = i;
            Rect.Color = (CR_Color){rand() % 255,rand() % 255,rand() % 255, 255, 1};
            CR_ConsoleClear;
            CR_RenderPrint(Render, CR_ColorMode_Background);
            sleep;
        }
    }
    CR_DestroyRender(Render);
    return 0;
}