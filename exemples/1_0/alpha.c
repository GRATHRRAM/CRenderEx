/*
    CRender - 1.0
    CRInput - 1.1
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
    CR_RenderFill(&Render, ' ', CR_VOID);

    char buff[16];
    uint8_t a=128;

    CR_Rect Rect;
    Rect.x = 0;
    Rect.y = 0;
    Rect.Height = 2;
    Rect.Width = 4;
    Rect.Char = ' ';
    Rect.Color = (CR_Color){255,0,0,a,1};//(CR_Color){Red,Green,Blue,Alpha,toDraw?}  Draw? 1=yes 0=no

    while(1) {
        CR_RenderFill(&Render, ' ', CR_VOID);
        CR_RenderSetPixel(&Render, 10,10,' ', CRC_GREEN);
        CR_RenderSetPixel(&Render, 5,5,' ', CRC_RED);
        Rect.Color = (CR_Color){255,0,0,a,1};
        CR_Rect2Render(&Render, Rect);

        sprintf(buff ,"Alpha: %d", a);
        CR_RenderDrawText(&Render, 0, ResolutionY - 1, 16, 1, buff, CRC_BLUE);

        CR_ConsoleClear;
        CR_RenderPrint(&Render, CR_ColorMode_Background);

        char inp = CRI_GetInput();
        if(inp == 'w') Rect.y--;
        if(inp == 's') Rect.y++;
        if(inp == 'a') Rect.x--;
        if(inp == 'd') Rect.x++;
        if(inp == 'q') break;

        if(inp == CRI_UpArrow)   a++;
        if(inp == CRI_DownArrow) a--;
    }

    CR_DestroyRender(&Render);
    return 0;
}
