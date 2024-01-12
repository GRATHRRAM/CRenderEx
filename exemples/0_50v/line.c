/*
    For CRenderEx - 0.50v
    For CRInput - 1.0v
    Creator: Grathrram
    start of dev: 12.01.2024
    License GNU GPL 3
*/

#include "CRenderEx.h"
#include "CRInput.h"
#include <stdbool.h>

#define ResolutionX 40
#define ResolutionY 10

int main(void) {
    CR_Render Render;
    CR_AllocRender(&Render, ResolutionX, ResolutionY);

    uint16_t StartX = 0, StartY = 0;
    uint16_t EndX = 5, EndY = 1;
    bool mode = false;

    char ArrayOfCharacters[] = "!@#$%^&*,./|?";
    uint8_t ArrayPointer = 0;

    while(1) {
        CR_RenderFill(&Render, ' ');
        CR_RenderDrawLine(&Render,
        StartX, StartY,
        EndX, EndY,
        ArrayOfCharacters[ArrayPointer]);

        CR_ConsoleClear;
        CR_RenderPrint(Render);

        ArrayPointer++;
        if(ArrayPointer > 12) ArrayPointer = 0;

        char Input = (char) CRI_GetInput();

        if(Input == 'a' && mode == false) StartX--;
        if(Input == 'd' && mode == false) StartX++;
        if(Input == 'w' && mode == false) StartY--;
        if(Input == 's' && mode == false) StartY++;
        if(Input == 'a' && mode == true)  EndX--;
        if(Input == 'd' && mode == true)  EndX++;
        if(Input == 'w' && mode == true)  EndY--;
        if(Input == 's' && mode == true)  EndY++;

        if(Input == 'f' || Input == 'm') mode = !mode;
        if(Input == 'q') break;
    }
    
}
