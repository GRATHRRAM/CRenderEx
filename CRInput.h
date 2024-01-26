/*
    CRenderInput - 1.0v
    Creator: Grathrram
    start of dev: 12.01.2024
    License GNU GPL 3
*/
#ifndef CRINPUT_H
#define CRINPUT_H

#define SIGINPE 3  //Input Error

#ifndef WIN32
#include <stdio.h>
#include <termios.h> 
#include <unistd.h> 

//arrow values in ascii encoding
#define CRI_UpArrow    65
#define CRI_DownArrow  66
#define CRI_LeftArrow  68
#define CRI_RightArrow 67

//Gets Input Without Enter
int CRI_GetInput(void){
    int Char;   
    static struct termios oldt, newt;
    tcgetattr( STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON);          
    tcsetattr( STDIN_FILENO, TCSANOW, &newt);
    Char = getchar();           
    tcsetattr( STDIN_FILENO, TCSANOW, &oldt);

    if(Char == 0) return SIGINPE;
    return Char;
}
#else 
#include <conio.h>

#define CRI_UpArrow    0x26
#define CRI_DownArrow  0x28
#define CRI_LeftArrow  0x25
#define CRI_RightArrow 0x27

//Gets Input Without Enter
int CRI_GetInput(void) {
    int Char = (int) getch();
    if(Char == 0) return SIGINPE;
    return Char;
}
#endif //!WIN32
#endif //!CRINPUT_H