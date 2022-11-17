#pragma FILE_IO
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>

typedef enum {
    false = 0,
    true = 1
} bool;

#define FILE_ERR -1
int FIOrun();
int OpenFile();
int test_1(int fd, char* filename);
int test_fcntl(int fd, char* filename);
void sercises_3_2(int fd1, int fd2);
void sercises_3_6();
