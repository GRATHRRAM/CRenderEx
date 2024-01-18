/*
    CRenderEx - 1.0v - alpha
    Creator: Grathrram
    start of dev: 17.01.2024
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

//\e[diffrent text; Text color; background]
//#define first_C "\e[0;30;40"
//#define End_c   "\e[8;37;47]"
//"\x1b[${bg};2;${red};${green};${blue}m\n"

#ifdef WIN32
#include <windows.h>
#define CR_ConsoleClear system("cls")
#else
#include <unistd.h>
#define CR_ConsoleClear system("clear")
#endif

//no BackGround
#define CR_Color_NoBackG 38
#define CR_Color_BackG   48

typedef struct CR_Color {
    uint8_t Red;
    uint8_t Green;
    uint8_t Blue;
} CR_Color;

//Character Render
typedef struct  CR_Render {
    char **Chars;
    uint32_t ResolutionX;
    uint32_t ResolutionY;
} CR_Render;

//Color Render
typedef struct CR_CRender {
    CR_Color **Pixel;
    uint32_t ResolutionX;
    uint32_t ResolutionY;
    char Filler;
} CR_CRender;


typedef struct CR_Rect {
    uint32_t x;
    uint32_t y;
    int32_t Width;
    int32_t Height;
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
uint8_t CR_InitCRender(CR_CRender *Render, uint32_t ResolutionX, uint32_t ResolutionY); //Sets Resolution of Render and allocs space
uint8_t CR_SetCRender (CR_CRender *Render, uint32_t ResolutionX, uint32_t ResolutionY); ////use if render alrady allocated

void CR_RenderFill (CR_Render *Render, char Character); //Fills Render With Characters
void CR_CRenderFill(CR_CRender *Render, CR_Color Color); //Fills Render With Color
void CR_RenderPrint(CR_Render Render);                  //Prints Graphics/Display You know what i mean
void CR_CRenderPrint(CR_CRender Render, uint8_t backGround); //Prints Graphics/Display You know what i mean

uint8_t CR_RenderSetChar(CR_Render *Render, uint32_t PositionX, uint32_t PositionY,  char Character);//Replace Character at given position
uint8_t CR_RenderDrawLine(CR_Render *Render, uint32_t StartX, uint32_t StartY, uint32_t EndX, uint32_t EndY, char Character);//Draws a line
uint8_t CR_CRenderDrawLine(CR_CRender *Render, uint32_t StartX, uint32_t StartY, uint32_t EndX, uint32_t EndY, CR_Color Color);//Draws a line
uint8_t CR_CRenderSetPixel(CR_CRender *Render, uint32_t PositionX, uint32_t PositionY,  CR_Color Color);//Replace Character at given position

uint8_t CR_SetText(CR_Text *Text, char* Text2Set);//changes Text

uint8_t CR_Rect2Render(CR_Render *Render, CR_Rect Rect);//Overwrites render with rect
uint8_t CR_Rect2CRender(CR_CRender *Render, CR_Rect Rect);//Overwrites render with rect
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

//use if render alrady allocated
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

uint8_t CR_InitCRender(CR_CRender *Render, uint32_t ResolutionX, uint32_t ResolutionY) {
    Render->Pixel  = (CR_Color**) malloc(sizeof(CR_Color*) * ResolutionY);
    for(uint32_t i=0; i < ResolutionY; ++i)
        Render->Pixel[i] = (CR_Color*) malloc(sizeof(CR_Color) * (ResolutionX + 1));
        
    if(Render->Pixel == NULL) return SIGOUTM;
    else {
        Render->ResolutionX = ResolutionX;
        Render->ResolutionY = ResolutionY;
    }
    return SIGNONE;
}

//use if render alrady allocated
uint8_t CR_SetCRender(CR_CRender *Render, uint32_t ResolutionX, uint32_t ResolutionY) {
    Render->Pixel = (CR_Color**) realloc(Render->Pixel, sizeof(CR_Color*) * ResolutionY);
    for(uint32_t i=0; i < ResolutionY; ++i)
        Render->Pixel[i] = (CR_Color*) realloc(Render->Pixel, sizeof(CR_Color) * (ResolutionX + 1));
        
    if(Render->Pixel == NULL) return SIGOUTM;
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

//Fills Render With Colors
void CR_CRenderFill(CR_CRender *Render, CR_Color Color) {
    for(uint32_t y=0; y < Render->ResolutionY; ++y) {
        for(uint32_t x=0; x < Render->ResolutionX; ++x) {
            Render->Pixel[y][x] = Color;
        }
    }
}

//Prints Graphics/Display You know what i mean
void CR_RenderPrint(CR_Render Render) {
    for(uint32_t y=0; y < Render.ResolutionY; ++y) {
        puts(Render.Chars[y]);
    }
}

//Prints Graphics/Display You know what i mean
void CR_CRenderPrint(CR_CRender Render, uint8_t backGround) {
    for(uint32_t y=0; y < Render.ResolutionY; ++y) {
        for(uint32_t x=0; x < Render.ResolutionX; ++x) {//"\x1b[${bg};2;${red};${green};${blue}m\n"
            printf("\x1b[%d;2;%d;%d;%dm", backGround, Render.Pixel[y][x].Red,
            Render.Pixel[y][x].Green, Render.Pixel[y][x].Blue);
            putchar(Render.Filler);
            printf("\x1b[0m");
        }
        putchar('\n');
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

uint8_t CR_CRenderDrawLine(CR_CRender *Render, uint32_t StartX, uint32_t StartY, 
uint32_t EndX, uint32_t EndY, CR_Color Color) {
    int dx,dy,Po;
    int k=0;
    CR_CRenderSetPixel(Render, StartX, StartY, Color);
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
                ReturnValue = CR_CRenderSetPixel(Render, ++xk, yk, Color);
			    Po=Po+(2*dy);
		    }
	        else {
                ReturnValue = CR_CRenderSetPixel(Render, ++xk, ++yk, Color);
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
                ReturnValue = CR_CRenderSetPixel(Render, xk, ++yk, Color);
			    Po=Po+(2*dx);
		    }
	        else {
                ReturnValue =  CR_CRenderSetPixel(Render, ++xk, ++yk, Color);
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
                ReturnValue = CR_CRenderSetPixel(Render, ++xk, yk, Color);
                Po=Po+(2*dy);
            }
            else {
                ReturnValue = CR_CRenderSetPixel(Render, ++xk, --yk, Color);
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
                ReturnValue = CR_CRenderSetPixel(Render, xk, --yk, Color);
                Po=Po+(2*dx);
            }
            else {
                ReturnValue = CR_CRenderSetPixel(Render, ++xk, --yk, Color);
                Po=Po+(2*dx)-(2*dy);
            }
        }
	}
    return ReturnValue;
}

//Replace Color at given position
uint8_t CR_CRenderSetPixel(CR_CRender *Render, uint32_t PositionX, uint32_t PositionY, CR_Color Color) {
    if(Render->ResolutionX <= PositionX ||
       Render->ResolutionY <= PositionY)
        return SIGOUTB;
    else Render->Pixel[PositionY][PositionX] = Color;
    return SIGNONE;
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

uint8_t CR_Rect2CRender(CR_CRender *Render, CR_Rect Rect) {
    uint8_t rval;
    if(Rect.Width < 0 && Rect.Height < 0){
        for(int32_t y = Rect.y; Rect.Height > y - Rect.y; --y) {
            for(int32_t x = Rect.x; Rect.Width > x - Rect.x; --x) {
                rval = CR_CRenderSetPixel(Render, x, y, Rect.Color);
            }
        }
    }
    else if(Rect.Width < 0) {
        for(uint32_t y = Rect.y; y - Rect.y < Rect.Height; ++y) {
            for(int32_t x = Rect.x; Rect.Width > x - Rect.x; --x) {
                rval = CR_CRenderSetPixel(Render, x, y, Rect.Color);
            }
        }
    }
    else if(Rect.Height < 0) {
        for(int32_t y = Rect.y; Rect.Height > y - Rect.y; --y) {
            for(uint32_t x = Rect.x; x - Rect.x < Rect.Width; ++x) {
                rval = CR_CRenderSetPixel(Render, x, y, Rect.Color);
            }
        }
    }
    else {
        for(uint32_t y = Rect.y; y - Rect.y < Rect.Height; ++y) {
            for(uint32_t x = Rect.x; x - Rect.x < Rect.Width; ++x) {
                rval = CR_CRenderSetPixel(Render, x, y, Rect.Color);
            }
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