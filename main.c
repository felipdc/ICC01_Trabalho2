#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "csv_parser.h"
#include "data_manager.h"


int main (int argc, char *argv[]) {

    FILE *fp;
    fp = fopen ("students.csv", "r");

	char *file_string = file_to_string(fp);
    fclose(fp);
    
    Data *students_data;
    size_t data_size = number_of_rows (file_string);
    students_data = malloc(sizeof(Data) * data_size);
    char ***data = string_data_to_matrix (file_string);
    data_to_struct (data, students_data, data_size);
    show_student_stats ("rob", students_data, data_size);

    show_specific_student_stats ("rob", get_stat_code ("work_grade"), students_data,
    								number_of_rows (file_string));

    display_data (students_data, number_of_rows (file_string));

    char *new_file_string = data_to_file_string (students_data, data_size);

    fp = fopen ("students.csv", "w");
   	string_to_csv(new_file_string, fp);
    fclose(fp);

    return 0;
}
