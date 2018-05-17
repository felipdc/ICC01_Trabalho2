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


int main (int argc, char *argv[]) {

    FILE *fp;
    fp = fopen ("students.csv", "r");

    char *file_string = file_to_string(fp);
   // char ***data = string_data_to_matrix(file_string);

    display_first_row ("robin", file_string);
    display_column ("work4pos", file_string);


    fclose(fp);
    return 0;
}
