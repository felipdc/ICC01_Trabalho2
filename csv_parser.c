#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "csv_parser.h"


char *file_to_string (FILE *fp) {
	int c = 0, char_counter = 0;
	char *file_string;
	file_string = malloc (num_of_char(fp));

	while ((c = fgetc(fp)) != EOF) file_string[char_counter++] = c;
	file_string[char_counter] = '\0';

	rewind(fp);
	return file_string;
}


char **get_row_by_name (char *name, char ***data, size_t column_size) {
	unsigned row_counter = 0;
	for (row_counter = 0; row_counter < column_size; ++row_counter) {
		if (strcmp (data[row_counter][0], name) == 0) {
			return data[row_counter];
		}
	}
	return NULL;
}


char **get_column_by_name (char *title, char ***data, char *file_string) {
	size_t column_idx = find_title_idx (title, data, file_string);
	size_t column_size = number_of_rows (file_string);
	char **column_data;
	// Return NULL if title does not exist
	if (column_idx == -1) {
		return NULL;
	}
	column_data = malloc (column_size * 256);
	for (int i = 0; i < column_size; ++i) {
		column_data[i] = malloc(256);
		strcpy (column_data[i], data[i][column_idx]);
	}
	return column_data;
}


size_t find_title_idx (char *title, char ***data, char *file_string) {
	unsigned col_counter = 0;
	size_t col_num = number_of_columns(file_string);
	for (col_counter = 0; col_counter < col_num; ++col_counter) {
		if (strcmp(title, data[0][col_counter]) == 0)  return col_counter;
	}
	return -1; // If title doesn`t exist return -1
}


size_t num_of_char (FILE *fp) {
	int c = 0;
	size_t num_of_char = 0;

	while ((c = fgetc(fp)) != EOF) ++num_of_char;

	rewind(fp);
	return num_of_char;
}


size_t number_of_rows (char *csv_string) {
	size_t row_counter = 0, char_counter = 0;
	while (csv_string[char_counter] != '\0') {
		if (csv_string[char_counter++] == '\n') ++row_counter;
	}
	return ++row_counter;
}


size_t number_of_columns (char *csv_string) {
	size_t column_counter = 0, char_counter = 0;
	while (csv_string[char_counter] != '\n') {
		if (csv_string[char_counter++] == ',') column_counter++;
	}
	return ++column_counter;
}


char ***string_data_to_matrix (char *csv_string) {
	char ***data;
	unsigned row_idx = 0, buffer_idx = 0, string_idx = 0, column_idx = 0;
	char buffer[256] = ""; // Hold information until next comma

	/** Memory allocation for data **/
	size_t num_of_rows = number_of_rows(csv_string);
    size_t num_of_cols = number_of_columns(csv_string);

	data = malloc(num_of_rows * num_of_cols * 256);
    for (int i = 0; i < num_of_rows + 1; ++i) {
    	data[i] = malloc(num_of_cols * 256);
    	for (int j = 0; j < num_of_cols + 1; ++j) {	
    		data[i][j] = malloc(256);
    	}
    }

	while (csv_string[string_idx] != '\0') {

		if (csv_string[string_idx] == ' ') {
			++string_idx;
			continue;
		}

		if (csv_string[string_idx] == ',') {
			buffer[buffer_idx] = '\0'; // Stop buffer
			buffer_idx = 0; // Reset buffer index
			strcpy (data[row_idx][column_idx], buffer);
			++string_idx;
			++column_idx;
			continue;
		}

		if (csv_string[string_idx] == '\n') {
			buffer[buffer_idx] = '\0'; // Stop buffer
			buffer_idx = 0; // Reset buffer index
			strcpy (data[row_idx][column_idx], buffer);
			++string_idx;
			++row_idx;
			column_idx = 0;
			continue;
		}

		buffer[buffer_idx] = csv_string[string_idx];
		++buffer_idx;
		++string_idx;

	}
	/** Assign to last column of last row **/
	buffer[buffer_idx] = '\0'; // Stop buffer
	buffer_idx = 0; // Reset buffer index
	strcpy (data[row_idx][column_idx], buffer);

	return data;
}


/** Display a formatted row given it`s first column name **/

void display_first_row (char *title, char *file_string) {
	char ***data = string_data_to_matrix (file_string);
	char **row = get_row_by_name (title, data, number_of_rows (file_string));
	size_t row_size = number_of_columns (file_string);

	// If name does not exist, return
	if (row == NULL) {
		return;
	}	

	for (int i = 0; i < row_size ; ++i) {
		printf("{%s: %s} ", data[0][i], row[i]);
	}
	printf("\n");
}

/** Display a formmated column given a csv title **/

void display_column (char *title, char *file_string) {
	char ***data = string_data_to_matrix (file_string);
	char **col = get_column_by_name (title, data, file_string);
	size_t col_size = number_of_rows (file_string);

	// If name does not exist, return
	if (col == NULL) {
		return;
	}

	printf ("%s: { ", col[0]);
	for (int i = 1; i < col_size; ++i) {
		printf("%s ", col[i]);
	}
	printf("}\n");

}


bool string_to_csv (const char *file_string, FILE *fp) {
	int result = fputs (file_string, fp);
	if (result < 0) return false; // In case of error
	return true; // else
}