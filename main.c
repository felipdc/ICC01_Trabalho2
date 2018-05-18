#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "csv_parser.h"


typedef enum {false, true} bool;


bool is_it_a_title (char title_to_check[], FILE *fp);
size_t number_of_columns (char *csv_string);
size_t number_of_rows (char *csv_string);


struct dat {
    char name[256];
    float test_grade[2];
    float work_grade[4];
    unsigned work_pos[4];
}; typedef struct dat Data;



void data_to_struct (char ***data, Data *students_data, size_t students_size) {
	for (int i = 1; i < students_size; ++i) {
		// Assign students names
		strcpy (students_data[i].name, data[i][0]);
		// Assign test grades
		students_data[i].test_grade[0] = atof (data[i][1]);
		students_data[i].test_grade[1] = atof (data[i][2]);
		// Assign work grades and work positions
		for (int j = 0; j < 4; ++j) {
			students_data[i].work_grade[j] = atof (data[i][j + 3]);
			students_data[i].work_pos[j] = atoi (data[i][j + 7]);
		}
	}
}


void show_student_stats (const char *student_name,
					 Data *students_data, size_t students_size) {
	for (int i = 0; i < students_size; ++i) {
		if (strcmp(students_data[i].name, student_name) == 0) {
			 printf("Name: %s\n", student_name);
			 printf("Test 1 Grade: %0.2f\n", students_data[i].test_grade[0]);
			 printf("Test 2 Grade: %0.2f\n", students_data[i].test_grade[1]);
			 for (int j = 0; j < 4; ++j) {
			 	printf("Work %d - Grade: %0.2f, Position: %u\n", j + 1,
			 	 students_data[i].work_grade[j], students_data[i].work_pos[j]);
			 }
			 return;
		}
	}
	printf("Name '%s' not found in database. \n", student_name);
}


int main (int argc, char *argv[]) {

    FILE *fp;
    fp = fopen ("students.csv", "r");

	char *file_string = file_to_string(fp);

    Data *students_data;
    students_data = malloc(sizeof(Data) * number_of_rows (file_string));

    char ***data = string_data_to_matrix (file_string);
    data_to_struct (data, students_data, number_of_rows (file_string));
    show_student_stats ("rob", students_data, number_of_rows (file_string));

    fclose(fp);
    return 0;
}
