#include<stdio.h>
#include<stdlib.h>

struct xyzStruct {
    int x, y, z;
};

int main(int argc, char *argv[]) {
    int input_num;
    char file_name_txt[] = "fileio.txt";
    char file_name_bin[] = "fileio.bin";
    struct xyzStruct coordinates;
    FILE *fptr;

    //
    // write to file in text mode
    printf("\n1# Write to file in text mode\n");

    input_num = 0;
    fptr = fopen(file_name_txt, "w");

    if (fptr == NULL) {
        printf("Error when reading file\n");
        exit(1);
    }

    printf("Enter number: ");
    scanf("%d", &input_num);

    fprintf(fptr, "%d\n", input_num);
    fclose(fptr);

    //
    // read from file in text mode
    printf("\n2# Read from file in text mode\n");
    input_num = 0;
    fptr = fopen(file_name_txt, "r");

    if (fptr == NULL) {
        printf("Error when reading file\n");
        exit(1);
    }

    fscanf(fptr, "%d", &input_num);
    printf("Read value + 1 is: %d\n", input_num + 1);
    fclose(fptr);

    //
    // write struct to the file in binary mode
    printf("\n3# Write struct to the file in binary mode\n");
    coordinates.x = 1;
    coordinates.y = 10;
    coordinates.z = 15;
    fptr = fopen(file_name_bin, "wb");

    if (fptr == NULL) {
        printf("Error when opening file for writing in binary mode\n");
        exit(1);
    }

    fwrite(&coordinates, sizeof(coordinates), 1, fptr);
    fclose(fptr);

    //
    // read struct from the file opened in binary mode
    printf("\n4# Read struct from the file opened in binary mode\n");
    coordinates.x = 0;
    coordinates.y = 0;
    coordinates.z = 0;
    fptr = fopen(file_name_bin, "rb");

    if (fptr == NULL) {
        printf("Error when opening file for reading in binary mode\n");
        exit(1);
    }

    fread(&coordinates, sizeof(coordinates), 1, fptr);
    printf("Read values x:%d y:%d z:%d\n", coordinates);
    fclose(fptr);

    return 0;

}