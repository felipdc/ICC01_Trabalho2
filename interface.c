#include <stdio.h>
#include <stdlib.h>
#include "data_manager.h"
#include "csv_parser.h"
#include "interface.h"
#include "utils.h"


/**
 *
 *	Tela inicial com as opcoes do programa
 *
 */

void display_splash_screen () {
	clrscr();
	printf ("\n\t##### Sistema de Consulta de alunos da discplina ICC-01 ####\n"
			"\t#\t\t\t\t\t\t\t   #\n\t#  Comandos:						   #"												
			"\n\t#\t\t\t\t\t\t\t   #\n\t#  0 - Sair						   #\n"
			"\t#  1 - Mostrar alunos cadastrados			   #\n"
			"\t#  2 - Mostrar alunos e notas das provas		   #\n" 
			"\t#  3 - Mostrar alunos e notas dos trabalhos + grupos	   #\n"
			"\t#  4 - Consultar nota das provas de um aluno especifico    #\n"
			"\t#  5 - Incluir/Remover nota de trabalho 		   #\n"
			"\t#  6 - Incluir/Remover nota de prova 			   #\n"
			"\t#  7 - Incluir/Remover novo aluno 			   #\n"
			"\t#  8 - Salvar e Sair 					   #\n"
			"\t# 							   #\n"
			"\t############################################################\n");
}


void back_to_menu_message () {
	printf ("\nAperte ENTER para voltar ao menu.\n");
	getchar ();
}


/*
 *	Le do usuario o nome de um determinado aluno
 */

char *get_input_name () {
	printf ("Digite o nome do aluno em questo.\n");
	char *name = malloc (256);
	scanf ("%s", name);
	getchar (); // Get return input from keyboard
	return name;
}


/*
 *	Interpreta a informacao que o usuario deseja consultar/alterar
 */

int get_specific_code () {
	clrscr ();
	printf ("\t###\tConsulta de dados especificos: \t ###\n\n"
			"\t#\tComandos:\n"
			"\t#\t1 - Consultar nome\n"
			"\t#\t2 - Consultar nota das provas\n"
			"\t#\t3 - Consultar nota dos trabalhos\n"
			"\t#\t4 - Consultar posicao nos grupos dos trabalhos\n"
			"\t#\t5 - Consultar tamanho do grupo de um aluno\n");

	int stat_code = 0;
	scanf ("%d", &stat_code);
	getchar ();
	return stat_code;
}


/*
 *	Decide se o usuario quer remover ou incluir uma informacao
*/

int include_or_remove () {
	int choose = -1;
	printf ("\t ### Digite 0 para incluir ou 1 para excluir\n");
	do {
		scanf ("%d", &choose);
		getchar ();
	} while (choose != 0 && choose != 1);

	return choose;
}


/*
 *	Le e interpreta as opcoes escolhidas pelo usuario na tela inicial
 */

void option_handle (Data *students_data, size_t data_size) {
	char option_read = ' ';
	while (option_read != '0') {
		display_splash_screen ();
		scanf ("%c", &option_read);
		getchar (); // Get return input from keyboard
		Option option = option_read - '0';
		switch (option) {
			case quit:
				return;
			case show_all_stud:
				clrscr ();
				show_specific_stats (NAME_ATRIB, students_data);
				break;
			case show_all_test:
				show_specific_stats (TEST_ATRIB, students_data);
				break;
			case show_all_work:
				show_specific_stats (WORK_G_ATRIB, students_data);
				break;
			case show_stud_spec_stat:
				show_specific_student_stats (get_input_name (), get_specific_code (),
											students_data);
				break;
			case incl_rm_work:
				insert_student_stat (get_input_name (), students_data, WORK_G_ATRIB);
				break;
			case incl_rm_test:
				insert_student_stat (get_input_name (), students_data, TEST_ATRIB);
				break;
			case incl_rm_stud:
				if (include_or_remove () == 1) {
					pop_student (get_input_name (), students_data);
				} else {
					push_student (get_input_name (), &students_data);
				}
				break;
			case save:
				save_to_csv (students_data, data_size);
				return;
				break;
			default:
				printf ("Opcao invalida, tente novamente.\n");
		}
		back_to_menu_message ();
	}
}


