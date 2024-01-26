/*
    CRenderEx - 1.0v - preBeta2
    Creator: Grathrram
    start of dev: 25.01.2024
    License GNU GPL 3
*/

#ifndef CRENDEREX_H
#define CRENDEREX_H

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define SIGNONE 0 //no error
#define SIGOUTM 1 //out of memory
//#define SIGOUTB 2 //out of borders not used
#define SIGINPE 3 //Input Error

#ifdef WIN32
#include <windows.h>
#define CR_ConsoleClear system("cls")
#else
#include <unistd.h>
#define CR_ConsoleClear system("clear")
#endif

//no BackGround
#define CR_ColorMode_Text       38
#define CR_ColorMode_Background 48

typedef struct CR_Color {
    uint8_t Red;
    uint8_t Green;
    uint8_t Blue;
    uint8_t Alpha;
    uint8_t draw;
} CR_Color;

typedef struct CR_Render {
    CR_Color **Pixel;
    char **Chars;
    uint32_t ResolutionX;
    uint32_t ResolutionY;
} CR_Render;

typedef struct CR_Rect {
    uint32_t x;
    uint32_t y;
    uint32_t Width;
    uint32_t Height;
    char Char;
    CR_Color Color;
} CR_Rect;

typedef struct CR_Text
{
    uint32_t x;
    uint32_t y;
    char *Text;
    uint32_t MaxWidth;
    uint32_t MaxHeight;
} CR_Text;

//If No Errors Returns 0 Else errsig (All Functions!!! if not void)
//If you see any error please fix or report. Thanks!!!

uint8_t CR_InitRender(CR_Render *Render, uint32_t ResolutionX, uint32_t ResolutionY); //Sets Resolution of Render and allocs space
uint8_t CR_SetRender (CR_Render *Render, uint32_t ResolutionX, uint32_t ResolutionY); ////use if render alrady allocated
void CR_DestroyRender(CR_Render Render);

void CR_RenderFill (CR_Render *Render, char Character, CR_Color Color); //Fills Render With Color
void CR_RenderPrint(CR_Render Render, uint8_t backGround); //Prints Graphics/Display You know what i mean

void CR_RenderDrawLine(CR_Render *Render, uint32_t StartX, uint32_t StartY, uint32_t EndX, uint32_t EndY, char Character, CR_Color Color);//Draws a line
void CR_RenderSetPixel(CR_Render *Render, uint32_t PositionX, uint32_t PositionY, char Character, CR_Color Color);//Replace Character at given position

uint8_t CR_SetText(CR_Text *Text, char* Text2Set);//changes Text

void CR_Rect2Render_Fill(CR_Render *Render, CR_Rect Rect);//Overwrites render with rect
void CR_Rect2Render_Outline(CR_Render *Render, CR_Rect Rect);
void CR_Text2Render(CR_Render *Render, CR_Text Text, CR_Color Color);//Overwrites render with Text

//calculates Transparency
CR_Color CR_ApplayAlpha(CR_Color Curent, CR_Color Background);

void CR_GetErrDesc(uint8_t Error); //prints description of error

//initiates Render
uint8_t CR_InitRender(CR_Render *Render, uint32_t ResolutionX, uint32_t ResolutionY) {
    Render->Chars = (char**) malloc(sizeof(char*) * ResolutionY);
    for(uint32_t i=0; i < ResolutionY; ++i)
        Render->Chars[i] = (char*) malloc(sizeof(char) * ResolutionX);
    if(Render->Chars == NULL) return SIGOUTM;

    Render->Pixel  = (CR_Color**) malloc(sizeof(CR_Color*) * ResolutionY);
    for(uint32_t i=0; i < ResolutionY; ++i)
        Render->Pixel[i] = (CR_Color*) malloc(sizeof(CR_Color) * (ResolutionX + 1));      
    if(Render->Pixel == NULL) return SIGOUTM;
    
    Render->ResolutionX = ResolutionX;
    Render->ResolutionY = ResolutionY;
    return SIGNONE;
}

//use if render already allocated
uint8_t CR_SetRender(CR_Render *Render, uint32_t ResolutionX, uint32_t ResolutionY) {
    Render->Chars = (char**) realloc(Render->Chars, sizeof(char*) * ResolutionY);
    for(uint32_t i=0; i < ResolutionY; ++i)
        Render->Chars[i] = (char*) realloc(Render->Chars[i], sizeof(char) * (ResolutionX + 1));
    if(Render->Chars == NULL) return SIGOUTM;

    Render->Pixel = (CR_Color**) realloc(Render->Pixel, sizeof(CR_Color*) * ResolutionY);
    for(uint32_t i=0; i < ResolutionY; ++i)
        Render->Pixel[i] = (CR_Color*) realloc(Render->Pixel, sizeof(CR_Color) * (ResolutionX + 1));
    if(Render->Pixel == NULL) return SIGOUTM;

    Render->ResolutionX = ResolutionX;
    Render->ResolutionY = ResolutionY;
    return SIGNONE;
}

void CR_DestroyRender(CR_Render Render) {
    free(Render.Chars);
    free(Render.Pixel);
}

//Fills Render With Colors
void CR_RenderFill(CR_Render *Render, char Character, CR_Color Color) {
    for(uint32_t y=0; y < Render->ResolutionY; ++y) {
        for(uint32_t x=0; x < Render->ResolutionX; ++x) {
            Render->Chars[y][x] = Character;
            Render->Pixel[y][x] = Color;
        }
    }
}

//Prints Graphics/Display You know what i mean
void CR_RenderPrint(CR_Render Render, uint8_t backGround) {
    for(uint32_t y=0; y < Render.ResolutionY; ++y) {
        for(uint32_t x=0; x < Render.ResolutionX; ++x) {
            if(Render.Pixel[y][x].draw) {
                printf("\x1b[%d;2;%d;%d;%dm", backGround, Render.Pixel[y][x].Red,
                Render.Pixel[y][x].Green, Render.Pixel[y][x].Blue);
            }
            putchar(Render.Chars[y][x]);
            printf("\x1b[0m");
        }
        putchar('\n');
    }
}

//Replace Color and char at given position
void CR_RenderSetPixel(CR_Render *Render, uint32_t PositionX, uint32_t PositionY, char Character, CR_Color Color) {
    if(Render->ResolutionX <= PositionX ||
       Render->ResolutionY <= PositionY)
        return;
    Render->Pixel[PositionY][PositionX] = CR_ApplayAlpha(Color, Render->Pixel[PositionY][PositionX]);
    Render->Chars[PositionY][PositionX] = Character;
}

//draws a line
void CR_RenderDrawLine(CR_Render *Render, uint32_t StartX, uint32_t StartY, 
uint32_t EndX, uint32_t EndY, char Character, CR_Color Color) {
    int dx,dy,Po;
    int k=0;
    CR_RenderSetPixel(Render, StartX, StartY, Character, Color);
	int xk=StartX;
	int yk=StartY;

    dx=(EndX-StartX);
    dy=(EndY-StartY);
    if(dy<=dx&&dy>0) {
	    dx=abs(dx);
	    dy=abs(dy);
 	    Po=(2*dy)-dx;
	    for(k=StartX;k<(int)EndX;k++) { 
	        if(Po<0) {	
                CR_RenderSetPixel(Render, ++xk, yk, Character, Color);
			    Po=Po+(2*dy);
		    }
	        else {
                CR_RenderSetPixel(Render, ++xk, ++yk, Character, Color);
			    Po=Po+(2*dy)-(2*dx);
		    }
	  }
	}
    else if(dy>dx&&dy>0) {
	    dx=abs(dx);
	    dy=abs(dy);
	    Po=(2*dx)-dy;
	    for(k=StartY;k<(int)EndY;k++) { 
	        if(Po<0) {	
                CR_RenderSetPixel(Render, xk, ++yk, Character, Color);
			    Po=Po+(2*dx);
		    }
	        else {
                CR_RenderSetPixel(Render, ++xk, ++yk, Character, Color);
			    Po=Po+(2*dx)-(2*dy);
		    }
	    }			
	}
    else if(dy>=-dx) {
        dx=abs(dx);
        dy=abs(dy);
        Po=(2*dy)-dx;
        for(k=StartX;k<(int)EndX;k++) { 
            if(Po<0) {	
                CR_RenderSetPixel(Render, ++xk, yk, Character, Color);
                Po=Po+(2*dy);
            }
            else {
                CR_RenderSetPixel(Render, ++xk, --yk, Character, Color);
                Po=Po+(2*dy)-(2*dx);
            }
        }
    }
    else if(dy<-dx) {
        dx=abs(dx);
        dy=abs(dy);
        Po=(2*dy)-dx;
        for(k=StartY;k>(int)EndY;k--) { 
            if(Po<0) {	
                CR_RenderSetPixel(Render, xk, --yk, Character, Color);
                Po=Po+(2*dx);
            }
            else {
                CR_RenderSetPixel(Render, ++xk, --yk, Character, Color);
                Po=Po+(2*dx)-(2*dy);
            }
        }
	}
}

//changes Text
uint8_t CR_SetText(CR_Text *Text, char* Text2Set) {
    if(Text->Text == NULL) {
        Text->Text = (char*) malloc(sizeof(char) * (strlen(Text2Set) + 1));
        if(Text->Text == NULL) return SIGOUTM;
        else Text->Text = Text2Set;
    }
    else if(strlen(Text2Set) >= strlen(Text->Text)){
        Text->Text = Text2Set;
    }
    else {
        Text->Text = (char*) realloc(Text->Text, sizeof(char) * (strlen(Text2Set) + 1));
        if(Text->Text == NULL) return SIGOUTM;
        else Text->Text = Text2Set;
    }
    return SIGNONE;
}

//Overwrites render with rect
void CR_Rect2Render_Fill(CR_Render *Render, CR_Rect Rect) {
    for(uint32_t y = Rect.y; y - Rect.y < Rect.Height; ++y) {
        for(uint32_t x = Rect.x; x - Rect.x < Rect.Width; ++x) {
           CR_RenderSetPixel(Render, x, y, Rect.Char, Rect.Color);
        }
    }
}

//Dont works Really Well
void CR_Rect2Render_Outline(CR_Render *Render, CR_Rect Rect) {
    for(uint32_t x = Rect.x; x < Rect.Width; ++x) {
        CR_RenderSetPixel(Render, x, Rect.y, Rect.Char, Rect.Color);
        CR_RenderSetPixel(Render, x, Rect.y + Rect.Height, Rect.Char, Rect.Color);
    }
    for(uint32_t y = Rect.y; y < Rect.Height; ++y) {
        CR_RenderSetPixel(Render, Rect.x, y, Rect.Char, Rect.Color);
        CR_RenderSetPixel(Render, Rect.x + Rect.Width, y, Rect.Char, Rect.Color);
    }
}

//Overwrites render with Text
void CR_Text2Render(CR_Render *Render, CR_Text Text, CR_Color Color) {
    uint32_t CharCounter = 0;

    for(uint32_t y = Text.y; y - Text.y < Text.MaxHeight; ++y) {
        for(uint32_t x = Text.x; x - Text.x < Text.MaxWidth; ++x) {
            if(CharCounter == strlen(Text.Text)) return;
            CR_RenderSetPixel(Render, x, y, Text.Text[CharCounter], Color);
            CharCounter++;
        }
    }
}

//calculates Transparency
CR_Color CR_ApplayAlpha(CR_Color Curent, CR_Color Background) {
    CR_Color buff;
    float alpha = Curent.Alpha / 255.0;
    float invAlpha = 1.0 - alpha;

    buff.Red   = (uint8_t) (Curent.Red * alpha + Background.Red * invAlpha);
    buff.Green = (uint8_t) (Curent.Green * alpha + Background.Green * invAlpha);
    buff.Blue  = (uint8_t) (Curent.Blue* alpha + Background.Blue * invAlpha);
    buff.draw  = Curent.draw;
    buff.Alpha = 255;
    return buff;
}

//prints description of error
void CR_GetErrDesc(uint8_t Error) {
    if(Error == 0) printf("CRender-> No Error. Youre Good!\n");                                     //SIGNONE 
    if(Error == 1) printf("CRender-> Out Of Memory. Error Occurs Mostly When Allocating Render\n"); //SIGOUTM
    if(Error == 2) printf("CRender-> Out Of Borders. (Warning) You haved tryed to do some thing out of render Borders\n"); //SIGOUTM
    if(Error == 3) printf("CRender-> Input Error. Cant Get Input."); //SIGINPE
    else printf("CRender-> Error Not Exist. Error Signal not Exitst!\n");
}

#endif //!CRENDEREX_H