#ifndef DATA_MANAGER_H_
#define DATA_MANAGER_H_


#define NAME_ATRIB 1
#define TEST_ATRIB 2
#define WORK_G_ATRIB 3
#define WORK_P_ATRIB 4
#define WORK_S_ATRIB 5


struct dat {
    char name[256];
    float test_grade[2];
    float work_grade[4];
    unsigned work_pos[4];
    struct {
    	float grade;
    	unsigned pos;
    	unsigned size;
    } work[4];
    struct dat *next;
}; typedef struct dat Data;


void data_to_struct (char ***data, Data *students_data, size_t students_size);
void data_to_node (char ***data, Data *current_data_node, size_t node_idx);
void show_student_stats (const char *student_name, Data *students_data);
void save_to_csv (Data *data, size_t data_size);
void show_specific_stats (int stat_code, Data *students_data);
Data * find_student (const char *student_name, Data *student_data);
float read_grade ();
unsigned read_group_pos ();

void insert_student_stat (const char *student_name, Data * students_data,
							int stat_code);


void show_specific_student_stats (const char *student_name,
					 				int stat_code, Data *students_data);

int get_stat_code (const char *goal_name);
void display_data (Data *students_data);
void push_student (const char *student_name, Data **students_data);
void pop_student (const char *student_name, Data *students_data);
char *data_to_file_string (Data *data, size_t data_size);



#endif // DATA_MANAGER_H_