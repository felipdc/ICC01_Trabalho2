#ifndef DATA_MANAGER_H_
#define DATA_MANAGER_H_


#define NAME_ATRIB 1
#define TEST_ATRIB 2
#define WORK_G_ATRIB 3
#define WORK_P_ATRIB 4


struct dat {
    char name[256];
    float test_grade[2];
    float work_grade[4];
    unsigned work_pos[4];
}; typedef struct dat Data;


void data_to_struct (char ***data, Data *students_data, size_t students_size);

void show_student_stats (const char *student_name, Data *students_data, 
						 size_t students_size);


void show_specific_stats (int stat_code, Data *students_data,
							size_t students_size);


void show_specific_student_stats (const char *student_name,
					 				int stat_code, Data *students_data,
					 				size_t students_size);

int get_stat_code (const char *goal_name);
void display_data (Data *students_data, size_t students_size);
char *data_to_file_string (Data *data, size_t data_size);



#endif // DATA_MANAGER_H_