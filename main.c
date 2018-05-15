#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/**
 *
 *	Possible operations:
 *		1- Display all csv titles - OK
 *		2- Display number of rows - OK
 *		3- Find if given attribbute exists in given column
 *		4- Assign a given column to a given array - OK
 *		5- Assign a given row to a given array - OK
 *		6- Find column index given column title - OK
 *		7- Display all titles - OK
 *
 **/

typedef enum {false, true} bool;


bool is_it_a_title (char title_to_check[], FILE *fp);
size_t line_number (FILE *fp);

struct cols {
    char name[256];
    unsigned pos;
}; typedef struct cols Cols;


struct students {
    char name[256];
    unsigned test_grade[2];
    unsigned work_grade[4];
    unsigned work_pos[4];
}; typedef struct students Stud;


int find_titles (FILE *fp) {
    int c = 0;
    char buffer[256];
    unsigned buffer_idx = 0;
    printf("\n");

    while ((c = fgetc(fp)) != '\n') {
        if (c == ' ') continue;
        if (c == ',') {
            buffer[buffer_idx] = '\0'; // Empty buffer
            buffer_idx = 0; // Reset buffer index
            printf("%s\n", buffer);
            continue;
        }
        buffer[buffer_idx++] = c;
    }

    buffer[buffer_idx-1] = '\0';
    printf("%s\n", buffer);
    rewind(fp);
    return 0;
}

/** 
 *
 *	Number of students will be given by number of lines - 1
 *
 **/

unsigned number_of_students (FILE *fp) {
	int c = 0;
	unsigned students_number = 0;

	while ((c = fgetc(fp)) != EOF) {
		if (c == '\n') ++students_number;
	}

	rewind(fp);
	return students_number;
}


int find_by_name (FILE *fp) {
    int c = 0;
    char buffer[256] = "";
    unsigned buffer_idx = 0;

    while ((c = fgetc(fp)) != EOF) {
        if (c == ' ') continue;
        if (c == ',') {
            if (strcmp(buffer, "rob") == 0) {
                printf("found %s\n", buffer);
                break;
            }
            /**
             *	Name will be always in first column. If not found in the first row,
             *		run throught the file until next line
             **/ 
            while ((c = fgetc(fp)) != '\n'); // Run until next line
            buffer[buffer_idx - 1] = '\0'; // Empty buffer
            buffer_idx = 0; // Reset buffer index
            continue;
        }
        buffer[buffer_idx++] = c;
    }
    rewind(fp);
    return 0;
}


bool is_it_a_title (char title_to_check[], FILE *fp) {
	int c = 0;
	char buffer[256] = "";
	unsigned buffer_idx = 0;

	while ((c = fgetc(fp)) != '\n') {
		if (c == ' ') continue; // Ignore blank spaces
		if (c == ',') {	// Evaluate current buffer
			buffer[buffer_idx] = '\0'; // Empty buffer
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

unsigned find_title_column (char title[], FILE *fp) {

	if (!is_it_a_title (title, fp)) return -1; 
	rewind(fp);

	int c = 0;
	char buffer[256] = "";

	//printf("%s\n", buffer);
	unsigned buffer_idx = 0, row_idx = 0;

	while ((c = fgetc(fp)) != '\n') {
		if (c == ' ') continue;
		if (c == ',') {
			buffer[buffer_idx] = '\0'; // Empty buffer
			buffer_idx = 0; // Reset buffer index
			if (strcmp(buffer, title) == 0) {
				rewind(fp);
				return row_idx;
			}
			++row_idx;
            continue;
		}
		buffer[buffer_idx++] = c;
	}

	buffer[buffer_idx - 1] = '\0';

	//	Evaluate last buffer
	if (strcmp(buffer, title) == 0) {
		rewind(fp);
		return row_idx;
	}
	rewind(fp);
	return -1;
}


void assign_row_to_array (FILE *fp, char *store_arr[], unsigned row) {
	int c = 0;
	char buffer[256] = "";
	unsigned buffer_idx = 0, line_count = 0, column_count = 0;
	// Look for the row
	while ((c = fgetc(fp)) != EOF) {
		if (row == line_count) {
			if (c == ' ') continue;
			if (c == ',') {
				buffer[buffer_idx] = '\0'; // Reset buffer
				buffer_idx = 0; // Reset buffer index
				strcpy (store_arr[column_count++], buffer);
				continue;
			}
			if (c == '\n') {
				buffer[buffer_idx - 1] = '\0'; // Reset buffer
				buffer_idx = 0; // Reset buffer index
				strcpy (store_arr[column_count++], buffer);
				break;
			}
			buffer[buffer_idx++] = c;
		}
		else if (c == '\n') {
			++line_count;
			continue;
		}
	}
	// Dealing with the last column
	if (row == line_count) {
		buffer[buffer_idx] = '\0'; // Reset buffer
		buffer_idx = 0; // Reset buffer index
		strcpy (store_arr[column_count++], buffer);
	}
	rewind(fp);
}


void assign_column_to_array (FILE *fp, char *store_arr[], unsigned column) {
	int c = 0;
	char buffer[256] = "";
	unsigned buffer_idx = 0, column_count = 0, line_count = 0;
	while ((c = fgetc(fp)) != EOF) {
		if (c == ' ') continue;
		if (c == ',') {
			buffer[buffer_idx] = '\0'; // Reset buffer
			buffer_idx = 0; // Reset buffer index
			if (column == column_count) {
				strcpy (store_arr[line_count], buffer);
				while ((c = fgetc(fp)) != '\n') {
					if (c == EOF) return;
				}
				++line_count;
				column_count = 0; // Reset column count
				continue;
			}
			++column_count;
			continue;
		}
		// Case where the title is in the last column
		if (c == '\n') {
			buffer[buffer_idx] = '\0'; // Reset buffer
			buffer_idx = 0; // Reset buffer index
			if (column == column_count) {
				strcpy (store_arr[line_count], buffer);
			}
			++line_count;
			column_count = 0;
			continue;
		}
		buffer[buffer_idx++] = c;
	}
	// Last line of the last column
	if (column == column_count) {
		buffer[buffer_idx] = '\0'; // Reset buffer
		buffer_idx = 0; // Reset buffer index
		strcpy (store_arr[line_count], buffer);
	}
	rewind(fp);
}

size_t line_number (FILE *fp) {

	int c = 0;
	size_t line_count = 0;

	while((c = fgetc(fp)) != EOF) {
		if (c == '\n') ++line_count;
	}

	rewind(fp);
	return ++line_count;

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
	file_string = malloc(num_of_char(fp));

	while ((c = fgetc(fp)) != EOF) file_string[char_counter++] = c;

	rewind(fp);
	return file_string;
}


unsigned number_of_rows (char *csv_string) {
	unsigned row_counter = 0, char_counter = 0;
	while (csv_string[char_counter] != '\0') {
		if (csv_string[char_counter++] == '\n') ++row_counter;
	}
	return ++row_counter;
}
 

int main (int argc, char *argv[]) {

    FILE *fp;
    fp = fopen ("students.csv", "r");

    char *file_string = file_to_string(fp);
    printf("%s\n", file_string);

    printf("%u\n", number_of_rows(file_string));

    fclose(fp);
    return 0;
}
