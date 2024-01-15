/*
    For CRenderEx - 0.50v
    For CRInput - 1.0v
    Creator: Grathrram
    start of dev: 15.01.2024
    License GNU GPL 3
*/

#include "CRenderEx.h"

#define ResolutionX 40
#define ResolutionY 10

int main(void) {
    CR_Render Render;
    CR_AllocRender(&Render, ResolutionX, ResolutionY);
    const char ArrayOfCharacters[] = "!@#$%^&*,./|?";

    uint32_t StartX, StartY;
    uint32_t EndX, EndY;

    printf("Resoluton X=40, Y=10\n");
    printf("StartX-> ");
    scanf("%d", &StartX);
    printf("StartY-> ");
    scanf("%d", &StartY);
    printf("EndX-> ");
    scanf("%d", &EndX);
    printf("EndY-> ");
    scanf("%d", &EndY);
    
    CR_RenderFill(&Render, ' ');
    CR_RenderDrawLine(&Render, StartX,
    StartY, EndX, EndY, ArrayOfCharacters[rand() % 14]);
    CR_RenderPrint(Render);
    return 0;
}