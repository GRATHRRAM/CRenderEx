/*
    For CRenderEx.h 0.50v
    For CRInput.h 1.0v
    by Grathrram
    start Dev 15.01.2024
*/

#include "CRenderEx.h"
#include "CRInput.h"

#define ResolutionX 40
#define ResolutionY 10

#ifdef WIN32
#include <windows.h>
#define sleep Sleep(50)
#else
#include <unistd.h>
#define sleep usleep(50 * 1000)
#endif

int main(void) {
    CR_Render Render;
    CR_SetRender(&Render, ResolutionX, ResolutionY);

    CR_Text Text;
    CR_SetText(&Text, "Text Works!");
    Text.x = 0;
    Text.y = 0;
    Text.MaxHeight = 1;
    Text.MaxWidth = (uint32_t) strlen("Text Works!");

    while (1) {
        CR_RenderFill(&Render, ' ');
        CR_Text2Render(&Render, Text);
        CR_RenderSetChar(&Render, Text.x + Text.MaxWidth, Text.y, '#');//Where Text width end
        CR_RenderSetChar(&Render, Text.x, Text.y + Text.MaxHeight, '#');//Where Text Height end

        CR_ConsoleClear;
        CR_RenderPrint(Render);

        char input = CRI_GetInput();

        if(input == 'w') Text.y--; 
        if(input == 's') Text.y++; 
        if(input == 'a') Text.x--; 
        if(input == 'd') Text.x++; 

        if(input == CRI_LeftArrow)  Text.MaxWidth--;
        if(input == CRI_RightArrow) Text.MaxWidth++;
        if(input == CRI_UpArrow)    Text.MaxHeight++;
        if(input == CRI_DownArrow)  Text.MaxHeight--;

        if(input == 'q') break; 
    }
    return 0;
}