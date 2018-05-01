#include <termios.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include "keyboard.h"
#include "bool.h"

bool keyboard_pressed(void){
    struct termios oldt, newt;
    int ch;
    int oldf;
    /*pega a flag que indica uma tecla digitada*/
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
    /*variavel int que vai esperar um char*/
    ch = getchar();
    /*se realmente um char foi digitado*/
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);
    /*a flag vai apontar e indicar algumas das teclas */
    if(ch != EOF){
        /*e assim retornar true*/
        ungetc(ch, stdin);
        return true;
    }
    /*senão retorna falso*/
    return false;
}