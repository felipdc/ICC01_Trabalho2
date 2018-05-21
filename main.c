#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "csv_parser.h"
#include "data_manager.h"
#include "interface.h"


void fill_list (Data *students_list, size_t size, char ***data);
void create_list (size_t data_size, char ***data);


void create_list (size_t data_size, char ***data) {
	Data *students_list;
	students_list = malloc (sizeof(Data));
	students_list->idx = 0;
	students_list->next = NULL;

	fill_list(students_list, data_size, data);
}


void fill_list (Data *students_list, size_t size, char ***data) {
	Data *current = students_list;

	for (int i = 1; i < size; ++i) {
		current->next = malloc(sizeof(Data));
		current->next->idx = i;
		current->next->next = NULL;
		current = current->next;
		data_to_node (data, current, i);
	}
}


void data_init () {

    FILE *fp;
    fp = fopen ("students.csv", "r");
    char *file_string = file_to_string(fp);
    fclose(fp);

    //Data *students_data;
    size_t data_size = number_of_rows (file_string);
    //students_data = malloc(sizeof(Data) * data_size);

    char ***data = string_data_to_matrix (file_string);
    create_list (data_size, data);

    //option_handle (students_data, data_size);
}


int main (int argc, char *argv[]) {
	data_init ();
 //    show_specific_student_statsnt_stats ("rob", students_data, data_size);

 //    show_specific_student_stats ("rob", get_stat_code ("work_grade"), students_data,
 //    								number_of_rows (file_string));

 //    display_data (students_data, number_of_rows (file_string));

 //    char *new_file_string = data_to_file_string (students_data, data_size);

 //    fp = fopen ("students.csv", "w");
 //   	string_to_csv(new_file_string, fp);
 //    fclose(fp);

    return 0;
}
