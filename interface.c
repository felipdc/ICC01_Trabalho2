#include <stdio.h>
#include <stdlib.h>
#include "data_manager.h"
#include "csv_parser.h"
#include "interface.h"

	
void display_splash_screen () {
	clrscr();
	printf ("\n\t##### Sistema de Consulta de alunos da discplina ICC-01 ####\n"
			"\t# \n\t#  Comandos:"
			"\n\t#\n\t#  0 - Sair\n"
			"\t#  1 - Mostrar alunos cadastrados\n"
			"\t#  2 - Mostrar alunos e notas das provas\n"
			"\t#  3 - Mostrar alunos e notas dos trabalhos + grupos\n"
			"\t#  3 - Consultar nota das provas de um aluno específico\n"
			"\t#  4 - Consultar nota dos trabalhos e grupos de um aluno específico\n"
			"\t#  5 - Incluir/Remover nota de trabalho\n"
			"\t#  6 - Incluir/Remover nota de prova\n"
			"\t#  7 - Incluir/Remover novo aluno\n");
}


void back_to_menu_message () {
	printf ("\nAperte ENTER para voltar ao menu.\n");
	getchar ();
}


char *get_input_name () {
	printf ("Digite o nome do aluno a ser consultado.\n");
	char *name = malloc (256);
	scanf ("%s", name);
	getchar (); // Get return input from keyboard
	return name;
}


int get_specific_code () {
	clrscr ();
	printf ("\t###\tConsulta de dados específicos: \t ###\n\n"
			"\t#\tComandos:\n"
			"\t#\t1 - Consultar nome\n"
			"\t#\t2 - Consultar nota das provas\n"
			"\t#\t3 - Consultar nota dos trabalhos\n"
			"\t#\t4 - Consultar posição nos grupos dos trabalhos\n");
	int stat_code = 0;
	scanf ("%d", &stat_code);
	getchar ();
	return stat_code;
}


void option_handle (Data *students_data, size_t data_size) {
	Option option = 1;
	while (option != 0) {
		display_splash_screen ();
		scanf ("%u", &option);
		getchar (); // Get return input from keyboard
		switch (option) {
			case quit:
				return;
			case show_all_stud:
				clrscr ();
				display_data (students_data, data_size);
				break;
			case show_all_test:
				break;
			case show_all_work:
				break;
			case show_stud_test:
				show_specific_student_stats (get_input_name (), get_specific_code (),
									students_data, data_size);
				break;
			case show_stud_work:
				break;
			case incl_rm_work:
				break;
			case incl_rm_test:
				break;
			case incl_rm_stud:
				break;
		}
		back_to_menu_message ();
	}
}


