#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#define MAX_FILENAME_LENGTH 50
#define MAX_DIR_LENGTH 50
#define MAX_FILES_PER_DIR 50

typedef struct {
    char filename[MAX_FILENAME_LENGTH];
} File;

typedef struct {
    char dirname[MAX_DIR_LENGTH];
    File files[MAX_FILES_PER_DIR];
    int file_count;
} Directory;

void createDirectory(char *dirname) {
   // mkdir(dirname, );
}

void createFile(char *dirname, char *filename) {
    char path[MAX_DIR_LENGTH + MAX_FILENAME_LENGTH];
    sprintf(path, "%s/%s", dirname, filename);
    FILE *file = fopen(path, "w");
    fclose(file);
}

void listFilesInDirectory(char *dirname) {
    printf("Files in directory '%s':\n", dirname);
    char command[MAX_DIR_LENGTH + 10];
    sprintf(command, "ls %s", dirname);
    system(command);
}

int main() {
    Directory directories[MAX_DIR_LENGTH];
    int dir_count = 0;

    int choice;
    do {
        printf("\n1. Create Directory\n2. Create File\n3. List Files in Directory\n4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter directory name: ");
                scanf("%s", directories[dir_count].dirname);
                createDirectory(directories[dir_count].dirname);
                dir_count++;
                break;
            case 2:
                if (dir_count == 0) {
                    printf("No directories created yet.\n");
                    break;
                }
                printf("Enter directory index to add file: ");
                int dir_index;
                scanf("%d", &dir_index);
                if (dir_index >= 0 && dir_index < dir_count) {
                    printf("Enter file name: ");
                    scanf("%s", directories[dir_index].files[directories[dir_index].file_count].filename);
                    createFile(directories[dir_index].dirname, directories[dir_index].files[directories[dir_index].file_count].filename);
                    directories[dir_index].file_count++;
                } else {
                    printf("Invalid directory index.\n");
                }
                break;
            case 3:
                if (dir_count == 0) {
                    printf("No directories created yet.\n");
                    break;
                }
                printf("Enter directory index to list files: ");
                int list_index;
                scanf("%d", &list_index);
                if (list_index >= 0 && list_index < dir_count) {
                    listFilesInDirectory(directories[list_index].dirname);
                } else {
                    printf("Invalid directory index.\n");
                }
                break;
            case 4:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice!\n");
        }
    } while (choice != 4);

    return 0;
}

