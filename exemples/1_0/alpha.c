/*
    CRender - 1.0 - prebeta
    CRInput - 1.0
    Creator - Grathrram
    Created - 18.01.2024
*/

#include "CRenderEx.h"
#include "CRInput.h"
#include <time.h>

#define ResolutionX 80
#define ResolutionY 20

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
    if(CR_InitRender(&Render, ResolutionX , ResolutionY)) return 1;
    CR_RenderFill(&Render, ' ', (CR_Color){0,0,0,255,1});

    char buff[16];
    uint8_t a=128;

    CR_Text text = {0};//its better if you make all null before CR_SetText
    text.x = 0;
    text.y = ResolutionY - 1;
    text.MaxHeight = 1;
    text.MaxWidth = ResolutionX;

    CR_Rect Rect;
    Rect.x = 0;
    Rect.y = 0;
    Rect.Height = 2;
    Rect.Width = 4;
    Rect.Char = ' ';
    Rect.Color = (CR_Color){255,0,0,a,1};//(CR_Color){Red,Green,Blue,Alpha,toDraw?}  Draw? 1=yes 0=no


    

    while(1) {
        CR_RenderFill(&Render, ' ', (CR_Color){0,0,0,255,1});
        CR_RenderSetPixel(&Render, 10,10,' ', (CR_Color){0,255,0,255,1});
        CR_RenderSetPixel(&Render, 5,5,' ', (CR_Color){0,0,255,255,1});

        Rect.Color = (CR_Color){255,0,0,a,1};
        CR_Rect2Render_Fill(&Render, Rect);

        sprintf(buff ,"Alpha: %d", a); CR_SetText(&text, buff); CR_Text2Render(&Render, text, (CR_Color){0,0,255,255,1});

        CR_ConsoleClear;
        CR_RenderPrint(Render, CR_ColorMode_Background);

        char inp = CRI_GetInput();
        if(inp == 'w') Rect.y--;
        if(inp == 's') Rect.y++;
        if(inp == 'a') Rect.x--;
        if(inp == 'd') Rect.x++;
        if(inp == 'q') break;

        if(inp == CRI_UpArrow)   a++;
        if(inp == CRI_DownArrow) a--;
    }

    return 0;
}