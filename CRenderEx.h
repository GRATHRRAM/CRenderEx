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

//ColorToPrintRegular
#define CR_ColorTPR_Black  "\e[0;30m"
#define CR_ColorTPR_Red    "\e[0;31m"
#define CR_ColorTPR_Green  "\e[0;32m"
#define CR_ColorTPR_Yellow "\e[0;33m"
#define CR_ColorTPR_Blue   "\e[0;34m"
#define CR_ColorTPR_Purple "\e[0;35m"
#define CR_ColorTPR_Cyan   "\e[0;36m"
#define CR_ColorTPR_White  "\e[0;37m"

//ColorToPrintBold
#define CR_ColorTPB_Black  "\e[1;30m"
#define CR_ColorTPB_Red    "\e[1;31m"
#define CR_ColorTPB_Green  "\e[1;32m"
#define CR_ColorTPB_Yellow "\e[1;33m"
#define CR_ColorTPB_Blue   "\e[1;34m"
#define CR_ColorTPB_Purple "\e[1;35m"
#define CR_ColorTPB_Cyan   "\e[1;36m"
#define CR_ColorTPB_White  "\e[1;37m"

//ColorToPritbackGround
#define CR_ColorTPG_Black  "\e[40m"
#define CR_ColorTPG_Red    "\e[41m"
#define CR_ColorTPG_Green  "\e[42m"
#define CR_ColorTPG_Yellow "\e[43m"
#define CR_ColorTPG_Blue   "\e[44m"
#define CR_ColorTPG_Purple "\e[45m"
#define CR_ColorTPG_Cyan   "\e[46m"
#define CR_ColorTPG_White  "\e[47m"

//For Function use
#define CR_Color_Black  0
#define CR_Color_Red    1
#define CR_Color_Green  2
#define CR_Color_Yellow 3
#define CR_Color_Blue   4
#define CR_Color_Purple 5
#define CR_Color_Cyan   6
#define CR_Color_White  7

#define CR_ColorBold_Black  8
#define CR_ColorBold_Red    9
#define CR_ColorBold_Green  10
#define CR_ColorBold_Yellow 11
#define CR_ColorBold_Blue   12
#define CR_ColorBold_Purple 13
#define CR_ColorBold_Cyan   14
#define CR_ColorBold_White  15

#define CR_ColorBackG_Black  16
#define CR_ColorBackG_Red    17
#define CR_ColorBackG_Green  18
#define CR_ColorBackG_Yellow 19
#define CR_ColorBackG_Blue   20
#define CR_ColorBackG_Purple 21
#define CR_ColorBackG_Cyan   22
#define CR_ColorBackG_White  23



#ifdef WIN32
#include <windows.h>
#define CR_ConsoleClear system("cls")
#else
#include <unistd.h>
#define CR_ConsoleClear system("clear")
#endif

//Character Render
typedef struct  CR_Render {
    char **Chars;
    uint32_t ResolutionX;
    uint32_t ResolutionY;
} CR_Render;

//Color Render
typedef struct CR_CRender {
    uint8_t **PixelColor;
    uint32_t ResolutionX;
    uint32_t ResolutionY;
    char Filler;
} CR_CRender;


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
uint8_t CR_SetRender (CR_Render *Render, uint32_t ResolutionX, uint32_t ResolutionY); ////use if render alrady allocated
uint8_t CR_InitCRender(CR_CRender *Render, uint32_t ResolutionX, uint32_t ResolutionY); //Sets Resolution of Render and allocs space
uint8_t CR_SetCRender (CR_CRender *Render, uint32_t ResolutionX, uint32_t ResolutionY); ////use if render alrady allocated

void CR_RenderFill (CR_Render *Render, char Character); //Fills Render With Characters
void CR_CRenderFill(CR_CRender *Render, uint8_t Color); //Fills Render With Color
void CR_RenderPrint(CR_Render Render);                  //Prints Graphics/Display You know what i mean
void CR_CRenderPrint(CR_CRender Render);                //Prints Graphics/Display You know what i mean

uint8_t CR_RenderSetChar(CR_Render *Render, uint32_t PositionX, uint32_t PositionY,  char Character);//Replace Character at given position
uint8_t CR_RenderDrawLine(CR_Render *Render, uint32_t StartX, uint32_t StartY, uint32_t EndX, uint32_t EndY, char Character);//Draws a line
uint8_t CR_CRenderSetPixel(CR_CRender *Render, uint32_t PositionX, uint32_t PositionY,  uint8_t Color);//Replace Character at given position

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
    Render->PixelColor = (uint8_t**) malloc(sizeof(uint8_t*) * ResolutionY);
    for(uint32_t i=0; i < ResolutionY; ++i)
        Render->PixelColor[i] = (uint8_t*) malloc(sizeof(uint8_t) * (ResolutionX + 1));
        
    if(Render->PixelColor == NULL) return SIGOUTM;
    else {
        Render->ResolutionX = ResolutionX;
        Render->ResolutionY = ResolutionY;
    }
    return SIGNONE;
}

//use if render alrady allocated
uint8_t CR_SetCRender(CR_CRender *Render, uint32_t ResolutionX, uint32_t ResolutionY) {
    Render->PixelColor = (uint8_t**) realloc(Render->PixelColor, sizeof(uint8_t*) * ResolutionY);
    for(uint32_t i=0; i < ResolutionY; ++i)
        Render->PixelColor[i] = (uint8_t*) realloc(Render->PixelColor, sizeof(uint8_t) * (ResolutionX + 1));
        
    if(Render->PixelColor == NULL) return SIGOUTM;
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
void CR_CRenderFill(CR_CRender *Render, uint8_t Color) {
    for(uint32_t y=0; y < Render->ResolutionY; ++y) {
        for(uint32_t x=0; x < Render->ResolutionX; ++x) {
            Render->PixelColor[y][x] = Color;
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
void CR_CRenderPrint(CR_CRender Render) {
    for(uint32_t y=0; y < Render.ResolutionY; ++y) {
        for(uint32_t x=0; x < Render.ResolutionX; ++x) {
            switch (Render.PixelColor[y][x]) {
                case 0:  printf("%c",CR_ColorTPR_Black); break;
                case 1:  printf("%c",CR_ColorTPR_Red     ); break;
                case 2:  printf("%c",CR_ColorTPR_Green   ); break;
                case 3:  printf("%c",CR_ColorTPR_Yellow  ); break;
                case 4:  printf("%c",CR_ColorTPR_Blue    ); break;
                case 5:  printf("%c",CR_ColorTPR_Purple  ); break;
                case 6:  printf("%c",CR_ColorTPR_Cyan    ); break;
                case 7:  printf("%c",CR_ColorTPR_White   ); break;
                case 8:  printf("%c",CR_ColorBold_Black  ); break;
                case 9:  printf("%c",CR_ColorBold_Red    ); break;
                case 10: printf("%c",CR_ColorBold_Green  ); break;
                case 11: printf("%c",CR_ColorBold_Yellow ); break;
                case 12: printf("%c",CR_ColorBold_Blue   ); break;
                case 13: printf("%c",CR_ColorBold_Purple ); break;
                case 14: printf("%c",CR_ColorBold_Cyan   ); break;
                case 15: printf("%c",CR_ColorBold_White  ); break;
                case 16: printf("%c",CR_ColorBackG_Black ); break;
                case 17: printf("%c",CR_ColorBackG_Red   ); break;
                case 18: printf("%c",CR_ColorBackG_Green ); break;
                case 19: printf("%c",CR_ColorBackG_Yellow); break;
                case 20: printf("%c",CR_ColorBackG_Blue  ); break;
                case 21: printf("%c",CR_ColorBackG_Purple); break;
                case 22: printf("%c",CR_ColorBackG_Cyan  ); break;
                case 23: printf("%c",CR_ColorBackG_White ); break;
                
                default:
                    printf("%c",CR_ColorTPR_White);
                break;
            }
            putchar(Render.Filler);
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

//Replace Color at given position
uint8_t CR_CRenderSetPixel(CR_CRender *Render, uint32_t PositionX, uint32_t PositionY, uint8_t Color) {
    if(Render->ResolutionX <= PositionX ||
       Render->ResolutionY <= PositionY)
        return SIGOUTB;
    else Render->PixelColor[PositionY][PositionX] = Color;
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