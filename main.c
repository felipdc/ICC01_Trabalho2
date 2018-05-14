#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef enum {false, true} bool;


bool is_it_a_title (char title_to_check[], FILE *fp);


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
				return true;
			}
            continue;
		}
		buffer[buffer_idx++] = c;
	}

	buffer[buffer_idx - 1] = '\0';

	//	Evaluate last buffer
	if (strcmp(buffer, title_to_check) == 0) {
		return true;
	}

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
		return row_idx;
	}

	return -1;
}


void assign_row_to_array (FILE *fp, char store_arr[], unsigned row) {
	int c = 0;
	char buffer[256] = "";
	unsigned buffer_idx = 0, row_count = 0;
	
	while ((c = fgetc(fp)) != EOF) {
		if (c == ' ') continue;
		if (c == ',') {
			buffer[buffer_idx] = '\0'; // Reset buffer
			buffer_idx = 0; // Reset buffer index
			if (row == row_count) {
				strcpy (store_arr, buffer);
				while ((c = fgetc(fp)) != '\n'); // Jump to next line
				continue;
			}
			++row_count;
			continue;
		}
		buffer[buffer_idx++] = c;
	}

}

int main (int argc, char *argv[]) {
    FILE *fp;
    fp = fopen ("students.csv", "r");
    int c = 0;
    while ((c  = fgetc(fp)) != EOF) {
        printf("%c", c);
    }
    rewind(fp);
    //find_titles(fp);
    //rewind(fp);
    //number_of_students(fp);
    //printf("\n%d\n", find_title_column("work1pos", fp));
    //rewind(fp);

    char foo[256];
    assign_row_to_array(fp, foo, 2);
    //printf("%s\n", foo);

    fclose(fp);
    return 0;
}
