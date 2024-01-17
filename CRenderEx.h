/*
    CRenderEx - 0.50v
    Creator: Grathrram
    start of dev: 12.01.2024
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
#define SIGOUTB 2 //out of borders
#define SIGINPE 3 //Input Error

#ifdef WIN32
#include <windows.h>
#define CR_ConsoleClear system("cls")
#else
#include <unistd.h>
#define CR_ConsoleClear system("clear")
#endif

typedef struct  CR_Render {
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
uint8_t CR_SetRender (CR_Render *Render, uint32_t ResolutionX, uint32_t ResolutionY);

void CR_RenderFill (CR_Render *Render, char Character); //Fills Render With Characters
void CR_RenderPrint(CR_Render Render);                  //Prints Graphics/Display You know what i mean

uint8_t CR_RenderSetChar(CR_Render *Render, uint32_t PositionX, uint32_t PositionY,  char Character);//Replace Character at given position
uint8_t CR_RenderDrawLine(CR_Render *Render, uint32_t StartX, uint32_t StartY, uint32_t EndX, uint32_t EndY, char Character);//Draws a line

uint8_t CR_SetText(CR_Text *Text, char* Text2Set);//changes Text

uint8_t CR_Rect2Render(CR_Render *Render, CR_Rect Rect);//Overwrites render with rect
uint8_t CR_Text2Render(CR_Render *Render, CR_Text Text);//Overwrites render with Text

void CR_GetErrDesc(uint8_t Error); //prints description of error

//Sets Resolution of Render and allocs space 
uint8_t CR_InitRender(CR_Render *Render, uint32_t ResolutionX, uint32_t ResolutionY) {
    Render->Chars = (char**) malloc(sizeof(char*) * ResolutionY);
    for(uint32_t i=0; i < ResolutionY; ++i)
        Render->Chars[i] = (char*) malloc(sizeof(char) * (ResolutionX + 1));
        
    if(Render->Chars == NULL) return SIGOUTM;
    else {
        Render->ResolutionX = ResolutionX;
        Render->ResolutionY = ResolutionY;
    }
    return SIGNONE;
}

uint8_t CR_SetRender(CR_Render *Render, uint32_t ResolutionX, uint32_t ResolutionY) {
    Render->Chars = (char**) realloc(Render->Chars, sizeof(char*) * ResolutionY);
    for(uint32_t i=0; i < ResolutionY; ++i)
        Render->Chars[i] = (char*) realloc(Render->Chars, sizeof(char) * (ResolutionX + 1));
        
    if(Render->Chars == NULL) return SIGOUTM;
    else {
        Render->ResolutionX = ResolutionX;
        Render->ResolutionY = ResolutionY;
    }
    return SIGNONE;
}

//Fills Render With Characters
void CR_RenderFill(CR_Render *Render, char Character) {
    for(uint32_t y=0; y < Render->ResolutionY; ++y) {
        for(uint32_t x=0; x < Render->ResolutionX; ++x) {
            Render->Chars[y][x] = Character;
        }
    }
}

//Prints Graphics/Display You know what i mean
void CR_RenderPrint(CR_Render Render) {
    for(uint32_t y=0; y < Render.ResolutionY; ++y) {
        puts(Render.Chars[y]);
    }
}

//Replace Character at given position
uint8_t CR_RenderSetChar(CR_Render *Render, uint32_t PositionX, uint32_t PositionY, char Character) {
    if(Render->ResolutionX <= PositionX ||
       Render->ResolutionY <= PositionY)
        return SIGOUTB;
    else Render->Chars[PositionY][PositionX] = Character;
    return SIGNONE;
}

//Draws a line
uint8_t CR_RenderDrawLine(CR_Render *Render, uint32_t StartX, uint32_t StartY,
uint32_t EndX, uint32_t EndY, char Character) {
    int dx,dy,Po;
    int k=0;
    CR_RenderSetChar(Render, StartX, StartY, Character);
	int xk=StartX;
	int yk=StartY;
    uint8_t ReturnValue = 0;

    dx=(EndX-StartX);
    dy=(EndY-StartY);
    if(dy<=dx&&dy>0) {
	    dx=abs(dx);
	    dy=abs(dy);
 	    Po=(2*dy)-dx;
	    for(k=StartX;k<(int)EndX;k++) { 
	        if(Po<0) {	
                ReturnValue = CR_RenderSetChar(Render, ++xk, yk, Character);
			    Po=Po+(2*dy);
		    }
	        else {
                ReturnValue = CR_RenderSetChar(Render, ++xk, ++yk, Character);
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
                ReturnValue = CR_RenderSetChar(Render, xk, ++yk, Character);
			    Po=Po+(2*dx);
		    }
	        else {
                ReturnValue =  CR_RenderSetChar(Render, ++xk, ++yk, Character);
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
                ReturnValue = CR_RenderSetChar(Render, ++xk, yk, Character);
                Po=Po+(2*dy);
            }
            else {
                ReturnValue = CR_RenderSetChar(Render, ++xk, --yk, Character);
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
                ReturnValue = CR_RenderSetChar(Render, xk, --yk, Character);
                Po=Po+(2*dx);
            }
            else {
                ReturnValue = CR_RenderSetChar(Render, ++xk, --yk, Character);
                Po=Po+(2*dx)-(2*dy);
            }
        }
	}
    return ReturnValue;
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
uint8_t CR_Rect2Render(CR_Render *Render, CR_Rect Rect) {
    uint8_t rval;
    for(uint32_t y = Rect.y; y - Rect.y < Rect.Height; ++y) {
        for(uint32_t x = Rect.x; x - Rect.x < Rect.Width; ++x) {
           rval = CR_RenderSetChar(Render, x, y, Rect.Char);
        }
    }
    return rval;
}

//Overwrites render with Text
uint8_t CR_Text2Render(CR_Render *Render, CR_Text Text) {
    uint32_t CharCounter = 0;
    uint8_t ReturnValue;

    for(uint32_t y = Text.y; y - Text.y < Text.MaxHeight; ++y) {
        for(uint32_t x = Text.x; x - Text.x < Text.MaxWidth; ++x) {
            if(CharCounter == strlen(Text.Text)) return ReturnValue;
            ReturnValue = CR_RenderSetChar(Render, x, y, Text.Text[CharCounter]);
            CharCounter++;
        }
    }
    return ReturnValue;
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