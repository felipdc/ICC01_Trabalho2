#include <stdio.h>
#include <stdlib.h>
#include <string.h>


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


bool is_it_a_title (char title_to_check[], FILE *fp) {
	int c = 0;
	char buffer[256] = "";
	unsigned buffer_idx = 0;

	while ((c = fgetc(fp)) != '\n') {
		if (c == ' ') continue; // Ignore blank spaces
		if (c == ',') {	// Evaluate current buffer
			buffer[buffer_idx] = '\0'; // Stop buffer
			buffer_idx = 0; // Reset buffer index
			if (strcmp(buffer, title_to_check) == 0) {
				rewind(fp);
				return true;
			}
            continue;
		}
		buffer[buffer_idx++] = c;
	}

	buffer[buffer_idx - 1] = '\0';

	//	Evaluate last buffer
	if (strcmp(buffer, title_to_check) == 0) {
		rewind(fp);
		return true;
	}
	rewind(fp);
	return false;
}

size_t find_title_idx (char *title, char ***data, char *file_string) {
	unsigned col_counter = 0;
	size_t col_num = number_of_columns(file_string);
	for (col_counter = 0; col_counter < col_num; ++col_counter) {
		if (strcmp(title, data[0][col_counter]) == 0)  return col_counter;
	}
	return -1; // If title doesn`t exist return -1
}


char **get_row_by_name (char *name, char ***data, size_t column_size) {
	unsigned row_counter = 0;
	for (row_counter = 0; row_counter < column_size; ++row_counter) {
		if (strcmp (data[row_counter][0], name) == 0) {
			return data[row_counter];
		}
	}
}


char **get_column_by_title (char *title, char ***data, char *file_string) {
	size_t column_idx = find_title_idx (title, data, file_string);
	size_t column_size = number_of_rows (file_string);
	char **column_data;
	column_data = malloc (column_size);
	for (int i = 0; i < column_size; ++i) {
		column_data[i] = malloc(256);
		strcpy (column_data[i], data[i][column_idx]);
	}
	return column_data;
}


size_t num_of_char (FILE *fp) {

	int c = 0;
	size_t num_of_char = 0;

	while ((c = fgetc(fp)) != EOF) ++num_of_char;

	rewind(fp);
	return num_of_char;
}


char *file_to_string (FILE *fp) {

	int c = 0, char_counter = 0;
	char *file_string;
	file_string = malloc (num_of_char(fp));

	while ((c = fgetc(fp)) != EOF) file_string[char_counter++] = c;
	file_string[char_counter] = '\0';

	rewind(fp);
	return file_string;
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


void string_data_to_matrix (char *csv_string, char ***data_matrix) {
	unsigned row_idx = 0, buffer_idx = 0, string_idx = 0, column_idx = 0;
	char buffer[256] = ""; // Store information until next ','

	while (csv_string[string_idx] != '\0') {

		if (csv_string[string_idx] == ' ') {
			++string_idx;
			continue;
		}

		if (csv_string[string_idx] == ',') {
			buffer[buffer_idx] = '\0'; // Stop buffer
			buffer_idx = 0; // Reset buffer index
			strcpy (data_matrix[row_idx][column_idx], buffer);
			++string_idx;
			++column_idx;
			continue;
		}

		if (csv_string[string_idx] == '\n') {
			buffer[buffer_idx] = '\0'; // Stop buffer
			buffer_idx = 0; // Reset buffer index
			strcpy (data_matrix[row_idx][column_idx], buffer);
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
	strcpy (data_matrix[row_idx][column_idx], buffer);
}


int main (int argc, char *argv[]) {

    FILE *fp;
    fp = fopen ("students.csv", "r");

    char *file_string = file_to_string(fp);
    
    char ***data;
    size_t num_of_rows = number_of_rows(file_string);
    size_t num_of_cols = number_of_columns(file_string);

    data = malloc(num_of_rows * num_of_cols * 256);
    for (int i = 0; i < num_of_rows; ++i) {
    	data[i] = malloc(num_of_cols * num_of_rows);
    	for (int j = 0; j < num_of_cols; ++j) {	
    		data[i][j] = malloc(256);
    	}
    }

    string_data_to_matrix (file_string, data);

    char **a = get_row_by_name("rob", data, num_of_rows);
    for (int i = 0; i < num_of_cols; ++i) {
    	printf("%s\n", a[i]);
    }

    char **b = get_column_by_title("mark1", data, file_string);
    for (int i = 0; i < num_of_rows; ++i) {
    	printf("%s\n", b[i]);
    }
    /** Free memory in data **/
    for (int i = 0; i < num_of_rows; ++i) {
    	for (int j = 0; j < num_of_cols; ++j) {
    		free(data[i][j]);
    	}
    	free(data[i]);
    }
   	free(data);

    fclose(fp);
    return 0;
}
