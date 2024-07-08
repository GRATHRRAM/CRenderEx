#define CRENDEREX_IMPLEMENTATION

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

#define SIGNONE 0 //no error
#define SIGOUTM 1 //out of memory
//#define SIGOUTB 2 //out of borders not used
#define SIGINPE 3 //Input Error

//no BackGround
#define CR_ColorMode_Text       38
#define CR_ColorMode_Background 48

#define CR_PI 3.1415926

typedef struct CR_Color {
    uint8_t Red;
    uint8_t Green;
    uint8_t Blue;
    uint8_t Alpha;
} CR_Color;

typedef struct CR_Render {
    CR_Color **Pixel;
    char **Chars;
    uint32_t ResolutionX;
    uint32_t ResolutionY;
} CR_Render;

typedef struct Vector2 {
  float x;
  float y;
} Vector2;

typedef struct Vector2i {
    int x;
    int y;
} Vector2i;

typedef struct CR_Rect {
    int32_t x;
    int32_t y;
    int32_t Width;
    int32_t Height;
    char Char;
    CR_Color Color;
} CR_Rect;

//If No Errors Returns 0 Else errsig (All Functions!!! if not void)
//If you see any error please fix or report. Thanks!!!

uint8_t CR_InitRender(CR_Render *Render, uint32_t ResolutionX, uint32_t ResolutionY); //Sets Resolution of Render and allocs space
void CR_DestroyRender(CR_Render *Render);//Frees Render (After that you can Init Another Render)

void CR_RenderFill (CR_Render *Render, char Character, CR_Color Color); //Fills Render With Color
void CR_RenderPrint(CR_Render *Render, uint8_t backGround, Vector2i SizeofPrint); //Prints Graphics/Display You know what i mean
void CR_RenderStretch(CR_Render *Render);//from 1:1 to 2:1 (normal proporcions for color rendering use text after stretch)

void CR_RenderSetPixel(CR_Render *Render, int32_t PositionX, int32_t PositionY, char Character, CR_Color Color);//Replace Character at given position
void CR_RenderDrawLine(CR_Render *Render, char Character,CR_Color Color, int32_t StartX, int32_t StartY, int32_t EndX, int32_t EndY);//Draws a line
void CR_RenderDrawRect(CR_Render *Render, int32_t x, int32_t y, int32_t h, int32_t w, char Char, CR_Color Color);//Draws Only outlines of Rect
void CR_RenderDrawRectNP(CR_Render *Render, int32_t x, int32_t y, int32_t w, int32_t h, char Char, CR_Color Color);//Draws Rect With Normal Proporcion
void CR_RenderDrawRectFill(CR_Render *Render, int32_t x, int32_t y, int32_t w, int32_t h, char Char, CR_Color Color);//Overwrites render with rect
void CR_RenderDrawText(CR_Render *Render, int32_t x, int32_t y, int32_t MaxWidth, int32_t MaxHeight, const char* Text, CR_Color Color);//draws Text in render
void CR_RenderDrawCircle(CR_Render *Render ,int x, int y, int Radius, char Char, CR_Color Color);//Draws only outlines of circle
void CR_RenderDrawCircleFill(CR_Render *Render, int x, int y, int Radius, char Char, CR_Color Color);//Draws Circle And fills it
void CR_RenderDrawEllipse(CR_Render *Render, int x, int y, int w, int h, char Char, CR_Color Color);//Draws only outlines of Elipse
void CR_RenderDrawEllipseFill(CR_Render *Render, int x, int y, int w, int h, char Char, CR_Color Color);//Draws elipse and fills it

void CR_Rect2Render(CR_Render *Render, CR_Rect Rect);//Overwrites render with rect

CR_Color CR_ApplayAlpha(CR_Color Curent, CR_Color Background);//calculates Transparency

bool CR_ColisionRect(int32_t x1 , int32_t y1, int32_t w1, int32_t h1, int32_t x2 , int32_t y2, int32_t w2, int32_t h2);
bool CR_ColisionElipse(int32_t x1 , int32_t y1, int32_t w1, int32_t h1, int32_t x2 , int32_t y2, int32_t w2, int32_t h2);

void CR_GetErrDesc(uint8_t Error); //prints description of error

float CR_Math_Deg2Rad(float Deg);
float CR_Math_Rad2Deg(float Rad);
Vector2 CR_Math_RotateLine(Vector2 Start, Vector2 End, double RadAngle);

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
void CR_RenderPrint(CR_Render *Render, uint8_t backGround, Vector2i SizeofPrint) {
    if(SizeofPrint.x > 0 || SizeofPrint.y > 0) {
        for(uint32_t y=0; y < Render->ResolutionY && y < (uint32_t) SizeofPrint.y; ++y) {
            for(uint32_t x=0; x < Render->ResolutionX && x < (uint32_t) SizeofPrint.x; ++x) {
                printf("\x1b[%d;2;%d;%d;%dm", backGround, Render->Pixel[y][x].Red,
                Render->Pixel[y][x].Green, Render->Pixel[y][x].Blue);
                putchar(Render->Chars[y][x]);
                printf("\x1b[0m");
            }
            putchar('\n');
        }
        return;
    }

    for(uint32_t y=0; y < Render->ResolutionY; ++y) {
        for(uint32_t x=0; x < Render->ResolutionX; ++x) {
            printf("\x1b[%d;2;%d;%d;%dm", backGround, Render->Pixel[y][x].Red,
            Render->Pixel[y][x].Green, Render->Pixel[y][x].Blue);
            putchar(Render->Chars[y][x]);
            printf("\x1b[0m");
        }
        putchar('\n');
    }
}

void CR_RenderStretch(CR_Render *Render) {
    CR_Render Render2 = {0};
    CR_InitRender(&Render2, Render->ResolutionX*2, Render->ResolutionY);

    uint32_t dx=0;
    
    for(uint32_t y=0;y < Render->ResolutionY; ++y) {
        dx=0;
        for(uint32_t x=0;x < Render->ResolutionX; ++x) {
            Render2.Chars[y][dx] = Render->Chars[y][x];
            Render2.Chars[y][dx+1] = Render->Chars[y][x];

            Render2.Pixel[y][dx].Red   = Render->Pixel[y][x].Red;
            Render2.Pixel[y][dx].Green = Render->Pixel[y][x].Green;
            Render2.Pixel[y][dx].Blue  = Render->Pixel[y][x].Blue;
            Render2.Pixel[y][dx].Alpha = Render->Pixel[y][x].Alpha;

            Render2.Pixel[y][dx+1].Red   = Render->Pixel[y][x].Red;
            Render2.Pixel[y][dx+1].Green = Render->Pixel[y][x].Green;
            Render2.Pixel[y][dx+1].Blue  = Render->Pixel[y][x].Blue;
            Render2.Pixel[y][dx+1].Alpha = Render->Pixel[y][x].Alpha;

            dx+=2;
        }
    }

    CR_DestroyRender(Render);
    CR_InitRender(Render, Render2.ResolutionX,Render2.ResolutionY);

    for(uint32_t y=0; y < Render->ResolutionY; ++y) {
        Render->Chars[y] = Render2.Chars[y];
    }

    for(uint32_t y=0; y < Render->ResolutionY; ++y) {
        for(uint32_t x=0; x < Render->ResolutionX; ++x) {
            Render->Pixel[y][x].Red   = Render2.Pixel[y][x].Red;
            Render->Pixel[y][x].Green = Render2.Pixel[y][x].Green;
            Render->Pixel[y][x].Blue  = Render2.Pixel[y][x].Blue;
            Render->Pixel[y][x].Alpha = Render2.Pixel[y][x].Alpha;
        }
    }

    CR_DestroyRender(&Render2);
}

//Replace Color and char at given position
void CR_RenderSetPixel(CR_Render *Render, int32_t PositionX, int32_t PositionY, char Character, CR_Color Color) {
    if(Render->ResolutionX <= (uint32_t) PositionX ||
       Render->ResolutionY <= (uint32_t) PositionY ||
       PositionX < 0 || PositionY < 0)
        return;
    Render->Pixel[PositionY][PositionX] = CR_ApplayAlpha(Color, Render->Pixel[PositionY][PositionX]);
    Render->Chars[PositionY][PositionX] = Character;
}

//draws a line
void CR_RenderDrawLine(CR_Render *Render, char Character,CR_Color Color, int32_t StartX, int32_t StartY, int32_t EndX, int32_t EndY) {
  int dx =  abs (EndX - StartX), sx = StartX < EndX ? 1 : -1;
  int dy = -abs (EndY - StartY), sy = StartY < EndY ? 1 : -1; 
  int err = dx + dy, e2; /* error value e_xy */
 
  for (;;){  /* loop */
    CR_RenderSetPixel(Render, StartX,StartY,Character,Color);
    if (StartX == EndX && StartY == EndY) break;
    e2 = 2 * err;
    if (e2 >= dy) { err += dy; StartX += sx; } /* e_xy+e_x > 0 */
    if (e2 <= dx) { err += dx; StartY += sy; } /* e_xy+e_y < 0 */
  }
}

void CR_RenderDrawText(CR_Render *Render, int32_t x, int32_t y, int32_t MaxWidth, int32_t MaxHeight, const char* Text, CR_Color Color) {
  size_t CharCounter = 0;

    for(int32_t ly = y; ly - y < MaxHeight; ++ly) {
        for(int32_t lx = x; lx - x < MaxWidth; ++lx) {
            if(CharCounter == strlen(Text)) return;
            CR_RenderSetPixel(Render, lx, ly, (char) Text[CharCounter], Color);
            CharCounter++;
        }
    }
} 

void CR_RenderDrawRect(CR_Render *Render, int32_t x, int32_t y, int32_t w, int32_t h, char Char, CR_Color Color) {
    for(int32_t CurentY = y; CurentY < y + h; ++CurentY) {
        for(int32_t CurentX = x; CurentX < x + w; ++CurentX) {
            CR_RenderSetPixel(Render,CurentX,CurentY,Char,Color);
        }
    }
}

void CR_RenderDrawRectNP(CR_Render *Render, int32_t x, int32_t y, int32_t w, int32_t h, char Char, CR_Color Color) {
  CR_RenderSetPixel(Render, x, y, Char, Color);
  CR_RenderSetPixel(Render, x, y + h, Char, Color);
  CR_RenderSetPixel(Render, x-1, y, Char, Color);
  CR_RenderSetPixel(Render, x + w + 1, y, Char, Color);
  
  for(int32_t lx = x + 1; lx < x + w + 1; ++lx) {
    CR_RenderSetPixel(Render, lx, y, Char, Color);
    CR_RenderSetPixel(Render, lx, y + h, Char, Color);
  }
  for(int32_t ly = y + 1; ly < y + h; ++ly) {
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
void CR_RenderDrawRectFill(CR_Render *Render, int32_t x, int32_t y, int32_t w, int32_t h, char Char, CR_Color Color) {
    for(int32_t ly = y; ly - y < h; ++ly) {
        for(int32_t lx = x; lx - x < w; ++lx) {
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
    for(int32_t y = Rect.y; y - Rect.y < Rect.Height; ++y) {
        for(int32_t x = Rect.x; x - Rect.x < Rect.Width; ++x) {
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
    buff.Alpha = 255;
    return buff;
}

bool CR_ColisionRect(int32_t x1 , int32_t y1, int32_t w1, int32_t h1, int32_t x2 , int32_t y2, int32_t w2, int32_t h2) {
 if (x1 + w1 < x2 ||
        x2 + w2 < x1 ||
        y1 + h1 < y2 ||
        y2 + h2 < y1) {
        return false;
    } else {
        return true;
    }
}

bool CR_ColisionElipse(int32_t x1 , int32_t y1, int32_t w1, int32_t h1, int32_t x2 , int32_t y2, int32_t w2, int32_t h2) {
    float distance = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
    float sumRadii = w1 + h1 + w2 + h2;
    if (distance <= sumRadii) return true;
    else return false;
}

//prints description of error
void CR_GetErrDesc(uint8_t Error) {
    if(Error == 0) printf("CRender-> No Error. Youre Good!\n");                                     //SIGNONE 
    if(Error == 1) printf("CRender-> Out Of Memory. Error Occurs Mostly When Allocating Render\n"); //SIGOUTM
    if(Error == 2) printf("CRender-> Out Of Borders. (Warning) You haved tryed to do some thing out of render Borders\n"); //SIGOUTM
    if(Error == 3) printf("CRender-> Input Error. Cant Get Input."); //SIGINPE
    else printf("CRender-> Error Not Exist. Error Signal not Exitst!\n");
}

inline float CR_Math_Deg2Rad(float Deg) {
  return (float) Deg * (CR_PI / 180);
}

inline float CR_Math_Rad2Deg(float Rad) {
  return (float) Rad * (180.0 / CR_PI);
}

Vector2 CR_Math_RotateLine(Vector2 Start, Vector2 End, double Angle) {
  int dx = End.x - Start.x, dy = End.y - Start.y;
  End.x = dx * cos(Angle) - dy * sin(Angle) + Start.x;
  End.y = dx * sin(Angle) + dy * cos(Angle) + Start.y;
  return End;
}
