#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "csv_parser.h"
#include "data_manager.h"
#include "interface.h"
#include "utils.h"


/*
 *	Preenche a lista encadeada com os dados do arquivo
 */

void fill_list (size_t size, char ***data) {
	Data *students_list = malloc (sizeof(Data));
	students_list->next = NULL;

	Data *current = students_list;	

	for (int i = 1; i < size; ++i) {
		current->next = malloc(sizeof(Data));
		current->next->next = NULL;
		current = current->next;
		data_to_node (data, current, i);
	}

	option_handle (students_list, size);
}


/*
 *	Inicia a leitura de dados do arquivo
 *	Caso nao haja arquivo, um novo arquivo eh criado
 *	com um estudante nulo
 */

void data_init () {

    FILE *fp;
    fp = fopen ("students.csv", "r");

    if (fp == NULL) {
    	printf ("Nenhum arquivo encontrado. "
    			"Criando novo arquivo... \n");
    	new_file ();
    	fp = fopen ("students.csv", "r");
    }

    char *file_string = file_to_string(fp);
    fclose(fp);

    size_t data_size = number_of_rows (file_string);
    char ***data = string_data_to_matrix (file_string);
    fill_list (data_size, data);
}


int main (int argc, char *argv[]) {
	data_init ();
    return 0;
}
