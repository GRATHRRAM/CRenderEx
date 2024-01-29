#include "CRenderEx.h"
#include "CRInput.h"

#define ResolutionX 50
#define ResolutionY 20

int main(void) {
    CR_Render Render;
    CR_InitRender(&Render, ResolutionX, ResolutionY);

    //rect1
    int x1 = 0;
    int y1 = 0;
    int w1 = 5;
    int h1 = 3;
    //rect2
    int x2 = 40;
    int y2 = 6;
    int w2 = 5;
    int h2 = 3;

    while (1) {
        CR_RenderFill(&Render, ' ', CRC_LIGHTGRAY);

        CR_RenderDrawRectFill(&Render, x1, y1, w1, h1, ' ', (CR_Color){ 112, 31, 126, 128, true});
        CR_RenderDrawRectFill(&Render, x2, y2, w2, h2, ' ', (CR_Color){ 0, 82, 172, 128, true} );

        bool Colison = CR_ColisionRect(x1, y1, w1, h1, x2, y2, w2, h2);

        if(Colison) 
            CR_RenderDrawText(&Render, (uint32_t) ResolutionX/2, (uint32_t) ResolutionY/2, 8, 1, "Colsion!", CR_BLACK);

        CR_ConsoleClear;
        CR_RenderPrint(&Render, CR_ColorMode_Background);

        char inp = CRI_GetInput();
        if(inp == 'w') y1--;
        if(inp == 's') y1++;
        if(inp == 'a') x1--;
        if(inp == 'd') x1++;
        if(inp == 'q') break;
    }

    CR_DestroyRender(&Render);
    return 0;
}