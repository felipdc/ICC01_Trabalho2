#ifndef INTERFACE_H_
#define INTEFACE_H_


#if defined (_WIN32) || defined (_WIN64)
#include <conio.h>
#else
#include <stdio.h>
#define clrscr() printf("\e[1;1H\e[2J")
#endif	

typedef enum {quit, show_all_stud, show_all_test, show_all_work,
			 	show_stud_test, show_stud_work, incl_rm_work,
			 	incl_rm_test, incl_rm_stud} Option;

void option_handle (Data *students_data, size_t data_size);
void display_splash_screen ();


#endif // INTERFACE_H_