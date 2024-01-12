#include "CRenderEx.h"
#include <time.h>
/*
    For CRenderEx.h 0.25v
    by Grathrram
    start Dev 11.01.2024
    *need to be fixed
*/
#define ResolutionX 40
#define ResolutionY 10

#ifdef WIN32
#define clear "cls"
#else
#define clear "clear"
#endif

int main(void)
{
    CR_Render Render;
    CR_AllocRender(&Render, ResolutionX, ResolutionY);
    CR_RenderFill(&Render, ' ');
    const char LooksArray[14] = "@#$%^&*-=~/|<>";

    srand(time(NULL));
    while (1)
    {
        system(clear);
        CR_Rect Rect;
        Rect.x = rand() % ResolutionX;
        Rect.y = rand() % ResolutionY;
        Rect.Width = rand() % ResolutionX / 2;
        Rect.Height = rand() % ResolutionY / 2;
        Rect.Char = LooksArray[rand() % 14];

        CR_Rect2Render(&Render, Rect);
        CR_RenderPrint(Render);
        getchar();
    }

    return 0;
}