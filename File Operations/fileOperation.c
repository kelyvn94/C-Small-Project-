#include <stdio.h>
#include <stdlib.h>

int main() {
    //File pointer
    FILE* fptr;

    //Creating file using fopen() function
    // with access mode "w"
    fptr = fopen("file.txt", "w");

    //Checking if file is created successfully
    if (fptr == NULL) {
        printf("Error! Could not create file\n");
    } else {
        printf("File created successfully\n");
    }

    return 0;

}