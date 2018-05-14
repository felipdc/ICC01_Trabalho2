#include <stdio.h>
#include <stdlib.h>
#include <string.h>


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
    while ((c = fgetc(fp)) != '\n') {
        if (c == ' ') continue;
        if (c ==  ',') {
            printf("\n%s", buffer);
            buffer_idx = 0;
            continue;
        }
        buffer[buffer_idx++] = c;
    }
    printf("\n%s", buffer);
    return 0;
}


int find_by_name (FILE *fp) {
    int c = 0;
    char buffer[256] = "";
    unsigned buffer_idx = 0;
    while ((c = fgetc(fp)) != EOF) {
        if (c == ' ') continue;
        if (c == ',') {
            // Test buffer if matches name
            printf("%s\n", buffer);
            if (strcmp(buffer, "rob") == 0) {
                printf("found %s\n", buffer);
                break;
            }
            // Name will be always in first column. If not found in the first row, run throught the file until next line
            while ((c = fgetc(fp)) != '\n');
            buffer[buffer_idx - 1] = '\0'; // Reboot buffer
            buffer_idx = 0; // Reboot buffer index
            continue;
        }
        buffer[buffer_idx++] = c;
    }
    return 0;
}


int main (int argc, char *argv[]) {
    FILE *fp;
    fp = fopen ("students.csv", "r");
    int c = 0;
    while ((c  = fgetc(fp)) != EOF) {
        printf("%c", c);
    }
    rewind(fp);
    find_by_name(fp);
    fclose(fp);
    return 0;
}
