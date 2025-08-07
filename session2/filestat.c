#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <file_path>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    char *filePath = argv[1];
    struct stat fileMetadata;
    if (lstat(filePath, &fileMetadata) == -1) {
        perror("lstat error");
        exit(EXIT_FAILURE);
    }
    printf("File Path:%s\n", filePath);

    printf("File Type:");
    if (S_ISREG(fileMetadata.st_mode)) {
        printf("Regular File\n");
    } else if (S_ISDIR(fileMetadata.st_mode)) {
        printf("Directory\n");
    } else if (S_ISLNK(fileMetadata.st_mode)) {
        printf("Symbolic Link\n");
    } else {
        printf("Other\n");
    }

    printf("Size:%ld bytes\n", fileMetadata.st_size);


    printf("Last Modified:%s", ctime(&fileMetadata.st_mtime));

    return 0;
}