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

//Gets Input Without Enter
int CRI_GetInput(void) {
    int Char = (int) getch();
    if(Char == 0) return SIGINPE;
    return Char;
}
#endif //!WIN32
#endif //!CRINPUT_H