#define CRENDEREX_IMPLEMENTATION

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define SIGNONE 0 //no error
#define SIGOUTM 1 //out of memory
//#define SIGOUTB 2 //out of borders not used
#define SIGINPE 3 //Input Error

//no BackGround
#define CR_ColorMode_Text       38
#define CR_ColorMode_Background 48

typedef struct CR_Color {
    uint8_t Red;
    uint8_t Green;
    uint8_t Blue;
    uint8_t Alpha;
    bool draw;
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

typedef struct CR_Text {
    uint32_t x;
    uint32_t y;
    char *Text;
    uint32_t MaxWidth;
    uint32_t MaxHeight;
} CR_Text;

uint8_t CR_InitRender(CR_Render *Render, uint32_t ResolutionX, uint32_t ResolutionY); //Sets Resolution of Render and allocs space
void CR_DestroyRender(CR_Render *Render);//Frees Render (After that you can Init Another Render)

void CR_RenderFill (CR_Render *Render, char Character, CR_Color Color); //Fills Render With Color
void CR_RenderPrint(CR_Render *Render, uint8_t backGround); //Prints Graphics/Display You know what i mean

void CR_RenderSetPixel(CR_Render *Render, uint32_t PositionX, uint32_t PositionY, char Character, CR_Color Color);//Replace Character at given position
void CR_RenderDrawLine(CR_Render *Render, uint32_t StartX, uint32_t StartY, uint32_t EndX, uint32_t EndY, char Character, CR_Color Color);//Draws a line
void CR_RenderDrawRect(CR_Render *Render, uint32_t x, uint32_t y, uint32_t h, uint32_t w, char Char, CR_Color Color);//Draws Only outlines of Rect
void CR_RenderDrawRectNP(CR_Render *Render, uint32_t x, uint32_t y, uint32_t w, uint32_t h, char Char, CR_Color Color);//Draws Rect With Normal Proporcion
void CR_RenderDrawRectFill(CR_Render *Render, uint32_t x, uint32_t y, uint32_t w, uint32_t h, char Char, CR_Color Color);//Overwrites render with rect
void CR_RenderDrawText(CR_Render *Render, uint32_t x, uint32_t y, uint32_t MaxWidth, uint32_t MaxHeight, const char* Text, CR_Color Color);//draws Text in render
void CR_RenderDrawCircle(CR_Render *Render ,int x, int y, int Radius, char Char, CR_Color Color);//Draws only outlines of circle
void CR_RenderDrawCircleFill(CR_Render *Render, int x, int y, int Radius, char Char, CR_Color Color);//Draws Circle And fills it
void CR_RenderDrawEllipse(CR_Render *Render, int x, int y, int w, int h, char Char, CR_Color Color);//Draws only outlines of Elipse
void CR_RenderDrawEllipseFill(CR_Render *Render, int x, int y, int w, int h, char Char, CR_Color Color);//Draws elipse and fills it

void CR_Rect2Render(CR_Render *Render, CR_Rect Rect);//Overwrites render with rect

CR_Color CR_ApplayAlpha(CR_Color Curent, CR_Color Background);//calculates Transparency

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

//Frees Render (After that you can Init Another Render)
void CR_DestroyRender(CR_Render *Render) {
    free(Render->Chars);
    free(Render->Pixel);
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
void CR_RenderPrint(CR_Render *Render, uint8_t backGround) {
    for(uint32_t y=0; y < Render->ResolutionY; ++y) {
        for(uint32_t x=0; x < Render->ResolutionX; ++x) {
            if(Render->Pixel[y][x].draw) {
                printf("\x1b[%d;2;%d;%d;%dm", backGround, Render->Pixel[y][x].Red,
                Render->Pixel[y][x].Green, Render->Pixel[y][x].Blue);
            }
            putchar(Render->Chars[y][x]);
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

void CR_RenderDrawText(CR_Render *Render, uint32_t x, uint32_t y, uint32_t MaxWidth, uint32_t MaxHeight, const char* Text, CR_Color Color) {
  uint32_t CharCounter = 0;

    for(uint32_t ly = y; ly - y < MaxHeight; ++ly) {
        for(uint32_t lx = x; lx - x < MaxWidth; ++lx) {
            if(CharCounter == strlen(Text)) return;
            CR_RenderSetPixel(Render, lx, ly, (char) Text[CharCounter], Color);
            CharCounter++;
        }
    }
} 

void CR_RenderDrawRect(CR_Render *Render, uint32_t x, uint32_t y, uint32_t w, uint32_t h, char Char, CR_Color Color) {
  CR_RenderSetPixel(Render, x, y, Char, Color);
  CR_RenderSetPixel(Render, x, y + h, Char, Color);
  
  for(uint32_t lx = x + 1; lx < x + w; ++lx) {
    CR_RenderSetPixel(Render, lx, y, Char, Color);
    CR_RenderSetPixel(Render, lx, y + h, Char, Color);
  }
  for(uint32_t ly = y + 1; ly < y + h; ++ly) {
    CR_RenderSetPixel(Render, x, ly, Char, Color);
    CR_RenderSetPixel(Render, x + w, ly, Char, Color);
  }
  CR_RenderSetPixel(Render, x + w, y+h, Char, Color);
}

void CR_RenderDrawRectNP(CR_Render *Render, uint32_t x, uint32_t y, uint32_t w, uint32_t h, char Char, CR_Color Color) {
  CR_RenderSetPixel(Render, x, y, Char, Color);
  CR_RenderSetPixel(Render, x, y + h, Char, Color);
  CR_RenderSetPixel(Render, x-1, y, Char, Color);
  CR_RenderSetPixel(Render, x + w + 1, y, Char, Color);
  
  for(uint32_t lx = x + 1; lx < x + w + 1; ++lx) {
    CR_RenderSetPixel(Render, lx, y, Char, Color);
    CR_RenderSetPixel(Render, lx, y + h, Char, Color);
  }
  for(uint32_t ly = y + 1; ly < y + h; ++ly) {
    CR_RenderSetPixel(Render, x, ly, Char, Color);
    CR_RenderSetPixel(Render, x + w, ly, Char, Color);
    CR_RenderSetPixel(Render, x-1, ly, Char, Color);
    CR_RenderSetPixel(Render, x + w + 1, ly, Char, Color);
  }
  CR_RenderSetPixel(Render, x + w, y+h, Char, Color);
  CR_RenderSetPixel(Render, x-1, y+h, Char, Color);
  CR_RenderSetPixel(Render, x + w + 1, y+h, Char, Color);
}

//Overwrites render with rect
void CR_RenderDrawRectFill(CR_Render *Render, uint32_t x, uint32_t y, uint32_t w, uint32_t h, char Char, CR_Color Color) {
    for(uint32_t ly = y; ly - y < h; ++ly) {
        for(uint32_t lx = x; lx - x < w; ++lx) {
           CR_RenderSetPixel(Render, lx, ly, Char, Color);
        }
    }
}

void CR_RenderDrawCircle(CR_Render *Render ,int x, int y, int Radius, char Char, CR_Color Color) {
    int lx = 0, ly = Radius;
    int d = 3 - 2 * Radius;

    while (ly >= lx) {
        CR_RenderSetPixel(Render, x + lx, y + ly, Char, Color);
        CR_RenderSetPixel(Render, x - lx, y + ly, Char, Color);
        CR_RenderSetPixel(Render, x + lx, y - ly, Char, Color);
        CR_RenderSetPixel(Render, x - lx, y - ly, Char, Color);
        CR_RenderSetPixel(Render, x + ly, y + lx, Char, Color);
        CR_RenderSetPixel(Render, x - ly, y + lx, Char, Color);
        CR_RenderSetPixel(Render, x + ly, y - lx, Char, Color);
        CR_RenderSetPixel(Render, x - ly, y - lx, Char, Color);
        lx++;

        if (d > 0) {
            ly--;
            d = d + 4 * (lx - ly) + 10;
        } else {
            d = d + 4 * lx + 6;
        }
        CR_RenderSetPixel(Render, x + lx, y + ly, Char, Color);
        CR_RenderSetPixel(Render, x - lx, y + ly, Char, Color);
        CR_RenderSetPixel(Render, x + lx, y - ly, Char, Color);
        CR_RenderSetPixel(Render, x - lx, y - ly, Char, Color);
        CR_RenderSetPixel(Render, x + ly, y + lx, Char, Color);
        CR_RenderSetPixel(Render, x - ly, y + lx, Char, Color);
        CR_RenderSetPixel(Render, x + ly, y - lx, Char, Color);
        CR_RenderSetPixel(Render, x - ly, y - lx, Char, Color);
    }
}

void CR_RenderDrawCircleFill(CR_Render *Render, int x, int y, int Radius, char Char, CR_Color Color) {
    CR_RenderDrawCircle(Render, x, y, Radius, Char, Color);

    for (int32_t ly = y - Radius; ly <= y + Radius; ly++) {
        for (int32_t lx = x - Radius; lx <= x + Radius; lx++) {
            if ((lx - x) * (lx - x) + (ly - y) * (ly - y) <= Radius * Radius) {
                CR_RenderSetPixel(Render, lx, ly, Char, Color);
            }
        }
    }
}

void CR_RenderDrawEllipse(CR_Render *Render, int x, int y, int w, int h, char Char, CR_Color Color) {
    int lx = 0, ly = h;
    long a_sqr = w * w;
    long b_sqr = h * h;
    long d1 = b_sqr - a_sqr * h + 0.25 * a_sqr;
    long dx = 2 * b_sqr * lx;
    long dy = 2 * a_sqr * ly;

    while (dx < dy) {
        CR_RenderSetPixel(Render, x + lx, y + ly, Char,Color);
        CR_RenderSetPixel(Render, x - lx, y + ly, Char,Color);
        CR_RenderSetPixel(Render, x + lx, y - ly, Char,Color);
        CR_RenderSetPixel(Render, x - lx, y - ly, Char,Color);

        lx++;
        dx += 2 * b_sqr;
        if (d1 < 0) {
            d1 += dx + b_sqr;
        } else {
            ly--;
            dy -= 2 * a_sqr;
            d1 += dx - dy + b_sqr;
        }
    }

    long d2 = b_sqr * (lx + 0.5) * (lx + 0.5) + a_sqr * (ly - 1) * (ly - 1) - a_sqr * b_sqr;
    while (ly >= 0) {
        CR_RenderSetPixel(Render, x + lx, y + ly, Char,Color);
        CR_RenderSetPixel(Render, x - lx, y + ly, Char,Color);
        CR_RenderSetPixel(Render, x + lx, y - ly, Char,Color);
        CR_RenderSetPixel(Render, x - lx, y - ly, Char,Color);

        ly--;
        dy -= 2 * a_sqr;
        if (d2 > 0) {
            d2 += a_sqr - dy;
        } else {
            lx++;
            dx += 2 * b_sqr;
            d2 += a_sqr + dx - dy;
        }
    }
}

void CR_RenderDrawEllipseFill(CR_Render *Render, int x, int y, int w, int h, char Char, CR_Color Color) {
  CR_RenderDrawEllipse(Render, x, y, w, h, Char, Color);
    for (int ly = y - h; ly <= y + h; ly++) {
        for (int lx = x - w; lx <= x + w; lx++) {
            if ((lx - x)*(lx - x) / (float)(w * w) + (ly - y)*(ly - y) / (float)(h * h) <= 1) {
                CR_RenderSetPixel(Render, lx, ly, Char,Color);
            }
        }
    }
}

//Overwrites render with rect
void CR_Rect2Render(CR_Render *Render, CR_Rect Rect) {
    for(uint32_t y = Rect.y; y - Rect.y < Rect.Height; ++y) {
        for(uint32_t x = Rect.x; x - Rect.x < Rect.Width; ++x) {
           CR_RenderSetPixel(Render, x, y, Rect.Char, Rect.Color);
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
