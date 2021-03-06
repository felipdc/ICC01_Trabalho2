#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "csv_parser.h"
#include "data_manager.h"
#include "utils.h"



/*
 *	Passa para a lista encadeada as informacoes dos alunos
 *	guardadas em um array 3x3
 */

void data_to_node (char ***data, Data *current_data_node, size_t node_idx) {
	// Assign students names
	strcpy (current_data_node->name, data[node_idx][0]);
	// Assign test grades
	current_data_node->test_grade[0] = atof (data[node_idx][1]);
	current_data_node->test_grade[1] = atof (data[node_idx][2]);
	// Assign work grades and work positions
	for (int j = 0; j < 4; ++j) {
		current_data_node->work[j].grade = atof (data[node_idx][j + 3]);
		current_data_node->work[j].pos = atoi (data[node_idx][j + 7]);
		current_data_node->work[j].size = atoi (data[node_idx][j + 11]);
	}
}


/*
 *	Imprime na tela todas as informacoes de todos os alunos
 */

void show_student_stats (const char *student_name, Data *students_data) {

	Data *current = students_data;

	while (current->next != NULL) {
		current = current->next;
		if (strcmp(current->name, student_name) == 0) {
			 printf("Name: %s\n", student_name);
			 printf("Nota Prova 1: %0.2f\n", current->test_grade[0]);
			 printf("Nota Prova 1: %0.2f\n", current->test_grade[1]);
			 for (int j = 0; j < 4; ++j) {
			 	printf("Trabalho %d - Nota: %0.2f, Posicao no grupo: %u\n", j + 1,
			 	 current->work[j].grade, current->work[j].pos);
			 }	
			 return;
		}
	}
	printf("Nome '%s' nao encontrado no banco de dados. \n", student_name);
}


/*
 *	Mostra informacoes especificas de todos os alunos
 */

void show_specific_stats (int stat_code, Data *students_data) {
	Data *current = students_data;
	while (current->next != NULL) {
		current = current->next;
		printf ("\nNome: %s\n\n", current->name);
		switch (stat_code) {
			case TEST_ATRIB:
				printf ("Nota prova 1: %0.2f\nNota prova 2: %0.2f\n", 
					current->test_grade[0],
					current->test_grade[1]);
				break;
			case WORK_G_ATRIB:
				for (int i = 0; i < 4; ++i) {
					printf("Trabalho %d: Nota: %0.2f, Poisicao no grupo: %u\n"
							"Tamanho do grupo: %u\n"
							"Nota individual: %0.2f\n\n",
					 		i + 1, current->work[i].grade,
					 		current->work[i].pos, current->work[i].size,
					 		indv_work_grade (current->work[i].grade, 
					 							current->work[i].pos,
					 							current->work[i].size));
				}
				break;
		}
	}
}


/*
 *	Mostra uma informacao especifica de um aluno especifico
 */


void show_specific_student_stats (const char *student_name,
					 				int stat_code, Data *students_data) {

	Data *current = find_student (student_name, students_data);

	if (current == NULL) {
		printf ("Nome '%s' nao encontrado no banco de dados. \n", student_name);
		return;
	}
	
	switch (stat_code) {
		case NAME_ATRIB:
			printf ("Nome: %s\n", current->name);
			break;
		case TEST_ATRIB:
			printf ("Nota Prova 1: %0.2f\nNota Prova 2: %0.2f\n", 
				current->test_grade[0],
				current->test_grade[1]);
			break;
		case WORK_G_ATRIB:
			for (int i = 0; i < 4; ++i) {
				printf ("Nota trabalho %d: %0.2f\n", i + 1, 
					current->work[i].grade);
			}
			break;
		case WORK_P_ATRIB:
			for (int i = 0; i < 4; ++i) {
				printf ("Posicao trabalho %d: %u\n", i + 1,
					current->work[i].pos);
			}
			break;
		case WORK_S_ATRIB:
			for (int i = 0; i < 4; ++i) {
				printf ("Número de alunos no grupo %d: %u\n", i + 1,
					current->work[i].size);
			}
			break;
		default:
			printf ("Stat not found in database\n");
	}

}


// Retorna o nó de determinado aluno


Data * find_student (const char *student_name, Data *student_data) {

	Data *current = student_data;

	while (current->next != NULL) {
		current = current->next;
		if (strcmp(current->name, student_name) == 0) {
			return current;
		}
	}
	// If not found
	return NULL;
}


// Insere informacao para um determinado aluno
	
void insert_student_stat (const char *student_name, Data * students_data,
							int stat_code) {

	Data *current = find_student (student_name, students_data);

	if (current == NULL) {
		printf ("Nome '%s' nao encontrado no banco de dados. \n", student_name);
		return;
	}

	float grade = 0.0;
	
	switch (stat_code) { 
		case TEST_ATRIB:
			for (int test_num = 0; test_num < 2; ++test_num) {
				printf ("Insira a nota da Prova %d: \n", test_num + 1);
				grade = read_grade ();
				current->test_grade[test_num] = grade;
			}
			break;
		case WORK_G_ATRIB:
			for (int work_num = 0; work_num < 4; ++work_num) {
				printf ("Insira a nota do Trabalho %d: \n", work_num + 1);
				grade = read_grade ();
				current->work[work_num].grade = grade;
			}
			break;
		case WORK_P_ATRIB:
			for (int work_num = 0; work_num < 4; ++work_num) {
				printf ("Insira a Posicao no grupo do Trabalho %d: \n",
						 work_num + 1);
				unsigned posis = read_group_pos ();
				current->work[work_num].pos = posis;
			}
			break;
		case WORK_S_ATRIB:
			for (int work_num = 0; work_num < 4; ++work_num) {
				printf ("Insira o tamanho do grupo do Trabalho %d: \n",
						 work_num + 1);
				unsigned sz = read_group_pos ();
				current->work[work_num].size = sz;
			}
			break;
		default:
			printf ("Stat not found in database\n");
	}

}


/*
 * Insere na lista encadeada um novo aluno com notas nulas
 */

void push_student (const char *student_name, Data ** student_head) {
	Data *new_node = malloc (sizeof (Data));
	Data *last = *student_head;

	// Add 0 to all other values
	strcpy (new_node->name, student_name);

	new_node->test_grade[0] = 0;
	new_node->test_grade[1] = 0;

	for (int i = 0; i < 4; ++i) {
		new_node->work[i].grade = 0;
		new_node->work[i].pos = 0;
		new_node->work[i].size = 1;
	}

	new_node->next = NULL;	

	while (last->next != NULL) last = last->next;

	last->next = new_node;	
}


/*
 *	Remove um aluno da lista
 */

void pop_student (const char *student_name, Data *student_data) {
	Data *current = student_data;
	Data *temp_node = NULL;
	while (current->next != NULL) {
		if (strcmp (current->next->name, student_name) == 0) {
			temp_node = current->next;
			current->next = temp_node->next;
			free (temp_node);
			printf ("Estudante removido da lista com sucesso!\n");
			return;
		}
		current = current->next;
	}
	// Else
	printf ("Nome '%s' nao encontrado no banco de dados. \n", student_name);
}


// Coloca a lista de alunos em formato de string


char *data_to_file_string (Data *data, size_t data_size) {
	
	Data *current = data;
	char *new_file_string;
	new_file_string = malloc (sizeof(Data)*data_size);
	char *buffer;
	buffer = malloc (sizeof(Data)*256);

	// Append csv title to new_file_string
	strcat (new_file_string, "name, mark1, mark2, markwork1, markwork2, "
								"markwork3, markwork4, work1pos, "
								"work2pos, work3pos, work4pos, "
								"group1sz, group2sz, group3sz, "
								"group3sz");

	while (current->next != NULL) {
		current = current->next;
		sprintf(buffer, 
				"\n%s, %0.2f, %0.2f, %0.2f, %0.2f, " 
				"%0.2f, %0.2f, %u, %u, %u, %u, " 
				"%u, %u, %u, %u", 
				current->name, current->test_grade[0],
				current->test_grade[1], current->work[0].grade,
				current->work[1].grade, current->work[2].grade,
				current->work[3].grade, current->work[0].pos,
				current->work[1].pos, current->work[2].pos,
		 		current->work[3].pos, current->work[0].size,
				current->work[1].size, current->work[2].size,
				current->work[3].size);
		strcat (new_file_string, buffer);
	}
	return new_file_string;
}


/*
 *	Salva todas as alteracoes para o disco no formato csv
 */

void save_to_csv (Data *data, size_t data_size) {
	FILE *fp;
	fp = fopen ("students.csv", "w");
	if (fp == NULL) {
		printf ("IO Error\n");
		return;
	}
	char *new_file_string = data_to_file_string (data, data_size);
	string_to_csv (new_file_string, fp);
	printf ("Dados salvos com sucesso!\n");
}