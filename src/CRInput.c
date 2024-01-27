#define CRINPUT_IMPLEMENTATION
#ifndef WIN32
#include <stdio.h>
#include <termios.h> 
#include <unistd.h> 
int CRI_GetInput(void){
    int Char;   
    static struct termios oldt, newt;
    tcgetattr( STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON);          
    tcsetattr( STDIN_FILENO, TCSANOW, &newt);
    Char = getchar();           
    tcsetattr( STDIN_FILENO, TCSANOW, &oldt);

    if(Char == 0) return 3;
    return Char;
}
#else 
#include <conio.h>
int CRI_GetInput(void) {
    int Char = (int) getch();
    if(Char == 0) return SIGINPE;
    return Char;
}
#endif //!WIN32