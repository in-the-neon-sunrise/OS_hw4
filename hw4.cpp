#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

const int size = 16;

// Циклическое чтение с использованием системного вызова read
int main(int argc, char *argv[]) {
    const char* inputFile = argv[1];
    const char* outputFile = argv[2];
    int     fd, fd1;
    char    buffer[size + 1];
    size_t read_bytes, write_bytes;
    
    if ((fd = open(inputFile, O_RDONLY)) < 0){
        printf("Can\'t open input file\n");
        exit(-1);
    }
    
    if ((fd1 = open(outputFile, O_WRONLY | O_CREAT)) < 0){
        printf("Can\'t open output file\n");
        exit(-1);
    }

    do {
        read_bytes = read(fd, buffer, size);
        if(read_bytes == -1) {
            printf("Can\'t read from input file\n");
            exit(-1);
        }
        write_bytes = write(fd1, buffer, read_bytes);
        if(write_bytes == -1) {
            printf("Can\'t write to output file\n");
            exit(-1);
        }
        buffer[read_bytes] = '\0';
    } while(read_bytes == size);

    printf("\nLast read_bytes = %ld\n", read_bytes);

    if(close(fd) < 0) {
        printf("Can\'t close input file\n");
    }
    if(close(fd1) < 0) {
        printf("Can\'t close output file\n");
    }
    return 0;
}
