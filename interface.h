#ifndef INTERFACE_H_
#define INTEFACE_H_


#if defined (_WIN32) || defined (_WIN64)
#include <conio.h>
#else
#include <stdio.h>
#define clrscr() printf("\e[1;1H\e[2J")
#endif	


void display_splash_screen ();


#endif // INTERFACE_H_