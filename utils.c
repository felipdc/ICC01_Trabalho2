#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "csv_parser.h"
#include "data_manager.h"
#include "utils.h"


/*
 *	Variavel global que guarda o nome das informacoes disponiveis
 */

static const char *g_stats_names[] = {"name", "test_grade", "work_grade", 
							"work_pos"};


/**
  *	@desc Le e retorna uma nota de 0 a 10 inserida pelo usuario
 */

float read_grade () {
	float grade = 0.0;
	scanf ("%f", &grade);
	getchar ();

	while (grade < 0 || grade > 10) {
		printf("Nota invalida, insira novamente!\n");
		scanf ("%f", &grade);
		getchar ();
	}

	return grade;

}


/*
 * Calcula a nota individual de um aluno de um determinado trabalho
 */

float indv_work_grade (float grade, unsigned pos, unsigned sz) {
	return (grade * (1 + 0.05 * (sz - 1)) * pow (0.9, pos));
}



/*
 *	@desc Le e retorna uma posicao maior do que 0
 */

unsigned read_group_pos () {
	unsigned group_pos = 0;
	scanf ("%u", &group_pos);
	getchar ();

	while (group_pos < 0) {
		printf("Posicao invalida, insira novamente!\n");
		scanf ("%u", &group_pos);
		getchar ();
	}

	return group_pos;
}


// Avalia qual informacao o usuario deseja ler / alterar

int get_stat_code (const char *goal_name) {
	if (strcmp (goal_name, g_stats_names[0]) == 0) {
		return NAME_ATRIB;
	}
	if (strcmp (goal_name, g_stats_names[1]) == 0) {
		return TEST_ATRIB;
	}
	if (strcmp (goal_name, g_stats_names[2]) == 0) {
		return WORK_G_ATRIB;
	}
	if (strcmp (goal_name, g_stats_names[3]) == 0) {
		return WORK_P_ATRIB;
	}
	return -1; // In case of no stat name
}


/*
 *	Cria novo arquivo com um aluno nulo caso arquivo nao exista
 */

void new_file () {
	FILE *fp;
	fp = fopen ("students.csv", "w");

	const char new_file_string[] = "name, mark1, mark2, markwork1, markwork2, "
								"markwork3, markwork4, work1pos, "
								"work2pos, work3pos, work4pos, "
								"group1sz, group2sz, group3sz, "
								"group3sz\n"
								"0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,"
								"0, 0, 0";

	fputs (new_file_string, fp);

	fclose (fp);
}
