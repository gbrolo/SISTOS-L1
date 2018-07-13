#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    FILE *file1, *file2;
    char filename[150], copy;

    printf("First file:\n");
    scanf("%s", filename);

    file1 = fopen(filename, "r");
    if (file1 == NULL) {
        printf("Invalid file %s \n", filename);
        exit(0);
    }

    printf("Second file:\n");
    scanf("%s", filename);

    file2 = fopen(filename, "w");
    if (file2 == NULL) {
        printf("Invalid file %s \n", filename);
        exit(0);
    }

    // read and copy
    copy = fgetc(file1);
    while (copy != EOF) {
        fputc(copy, file2);
        copy = fgetc(file1);
    }

    printf("Finishing copying files!\n");

    fclose(file1);
    fclose(file2);

    return 0;
}