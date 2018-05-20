#ifndef CSV_PARSER_H_
#define CSV_PARSER_H_


typedef enum {false, true} bool;


bool string_to_csv (const char *file_string, FILE *fp);
char *file_to_string (FILE *fp);
char ***string_data_to_matrix (char *csv_string);
size_t find_title_idx (char *title, char ***data, char *file_string);
size_t num_of_char (FILE *fp);
size_t number_of_rows (char *csv_string);
size_t number_of_columns (char *csv_string);


#endif // CSV_PARSER_H_