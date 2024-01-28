/*
    CRender - 1.0
    Creator - Grathrram
    Created - 28.01.2024
*/

#include "CRenderEx.h"
#include <time.h>

#define ResolutionX 80
#define ResolutionY 20

#ifdef WIN32
#include <windows.h>
#define sleep Sleep(100)
#else
#include <unistd.h>
#define sleep usleep(100 * 1000)
#endif

uint32_t GetPosX();
uint32_t GetPosY();

int main(void) {
    long Time;
    int Alpha=255;
    uint8_t ALR = 0;

    printf("Seed? ");
    scanf("%ld", &Time);
    printf("Alpha?(0 == Random) ");
    scanf("%i", &Alpha);
    if(Alpha == 0) ALR = 1;

    srand(time(NULL));
    CR_Render Render;
    CR_InitRender(&Render, ResolutionX , ResolutionY);
    CR_RenderFill(&Render, ' ', CR_BLACK);

    while(1) {
      if(ALR) Alpha = rand() % 255;
      CR_RenderDrawRectFill(&Render,
      GetPosX(),
      GetPosY(),
      GetPosX(),
      GetPosY(),
      ' ',
      (CR_Color){rand() % 255, rand() % 255, rand() % 255,(uint8_t)Alpha, 1});
      CR_ConsoleClear;
      CR_RenderPrint(&Render, CR_ColorMode_Background);
      sleep;
    }

    CR_DestroyRender(&Render);
    return 0;
}

uint32_t GetPosX() {
  uint32_t randval = rand() % ResolutionX + 50;
  return randval - 50;
}

uint32_t GetPosY() {
  uint32_t randval = rand() % ResolutionY + 50;
  return randval - 50;
}