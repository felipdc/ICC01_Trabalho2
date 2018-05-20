#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "csv_parser.h"
#include "data_manager.h"


const char *g_stats_names[] = {"name", "test_grade", "work_grade", 
							"work_pos"};


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


void show_specific_student_stats (const char *student_name,
					 				int stat_code, Data *students_data,
					 				size_t students_size) {
	int student_name_index = -1;
	// Find student name in data
	for (int i = 0; i < students_size; ++i) {
		if (strcmp(students_data[i].name, student_name) == 0) {
			student_name_index = i;
			break;
		}
	} if (student_name_index == -1) {
		printf ("Name '%s' not found in database. \n", student_name);
		return;
	}
	
	switch (stat_code) {
		case NAME_ATRIB:
			printf ("Name: %s\n", students_data[student_name_index].name);
			break;
		case TEST_ATRIB:
			printf ("Test grade 1: %0.2f\nTest grade 2: %0.2f\n", 
				students_data[student_name_index].test_grade[0],
				students_data[student_name_index].test_grade[1]);
			break;
		case WORK_G_ATRIB:
			for (int i = 0; i < 4; ++i) {
				printf("Work %d grade: %0.2f\n", i + 1, 
					students_data[student_name_index].work_grade[i]);
			}
			break;
		case WORK_P_ATRIB:
			for (int i = 0; i < 4; ++i) {
				printf("Work %d position: %u\n", i + 1,
					students_data[student_name_index].work_pos[i]);
			}
			break;
	}

}


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


void display_data (Data *students_data, size_t students_size) {
	printf ("\nName:\tTest 1 Grade:\tTest 2 Grade:\tWork 1 Grade:\t"
			"Work 2 Grade:\n");

	for (int i = 1; i < students_size; ++i) {
		printf("%s\t", students_data[i].name);
		printf("%0.2f\t\t", students_data[i].test_grade[0]);
		printf("%0.2f\t\t", students_data[i].test_grade[1]);
		printf("%0.2f\t\t", students_data[i].work_grade[0]);
		printf("%0.2f\n", students_data[i].work_grade[1]);
	}

	printf ("\nWork 3 Grade:\tWork 4 Grade:\tWork 1 Pos:\tWork 2 Pos:\t"
			"Work 3 Pos:\n");

	for (int i = 1; i < students_size; ++i) {
		printf("%0.2f\t\t", students_data[i].work_grade[2]);
		printf("%0.2f\t\t", students_data[i].work_grade[3]);
		printf("%u\t\t", students_data[i].work_pos[0]);
		printf("%u\t\t", students_data[i].work_pos[1]);
		printf("%u\n", students_data[i].work_pos[2]);
	}

	printf ("\nWork 4 Pos:\n");

	for (int i = 1; i < students_size; ++i) {
		printf("%u\n", students_data[i].work_pos[3]);
	}
}


char *data_to_file_string (Data *data, size_t data_size) {
	char *new_file_string;
	new_file_string = malloc (sizeof(Data)*data_size);
	char *buffer;
	buffer = malloc (sizeof(Data)*256);

	// Append csv title to new_file_string
	strcat (new_file_string, "name, mark1, mark2, markwork1, markwork2, "
								"markwork3, markwork4, work1pos, "
								"work2pos, work3pos, work4pos");

	for (int i = 1; i < data_size; ++i) {
		sprintf(buffer, 
				"\n%s, %0.2f, %0.2f, %0.2f, %0.2f, " 
				"%0.2f, %0.2f, %u, %u, %u, %u", 
				data[i].name, data[i].test_grade[0],
				data[i].test_grade[1], data[i].work_grade[0],
				data[i].work_grade[1], data[i].work_grade[2],
				data[i].work_grade[3], data[i].work_pos[0],
				data[i].work_pos[1], data[i].work_pos[2],
		 		data[i].work_pos[3]);
		strcat (new_file_string, buffer);
	}
	return new_file_string;
}