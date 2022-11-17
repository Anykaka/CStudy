#include "filedir.h"

void dumpstat(int argc, char *argv[]) {
    struct stat buf;
    
    for (int i = 1; i < argc; i++) {
        printf("arg[%d] is : %s.\n", i, argv[i]);
        if (stat(argv[i], &buf) < 0) {
            printf("Get %s stat err.\n", argv[i]);
            continue;
        }
        if (S_ISREG(buf.st_mode)) {
            printf("%s st_mod is %d S_ISREG.\n", argv[i], buf.st_mode);
        }
        else if (S_ISBLK(buf.st_mode)) {
            printf("%s st_mod is %d S_ISBLK.\n", argv[i], buf.st_mode);
        }
        else if (S_ISCHR(buf.st_mode)) {
            printf("%s st_mod is %d S_ISCHR.\n", argv[i], buf.st_mode);
        }
        else if (S_ISDIR(buf.st_mode)) {
            printf("%s st_mod is %d S_ISDIR.\n", argv[i], buf.st_mode);
        }
        else if (S_ISFIFO(buf.st_mode)) {
            printf("%s st_mod is %d S_ISFIFO.\n", argv[i], buf.st_mode);
        }
        else if (S_ISLNK(buf.st_mode)) {
            printf("%s st_mod is %d S_ISLNK.\n", argv[i], buf.st_mode);
        }
        else if (S_ISSOCK(buf.st_mode)) {
            printf("%s st_mod is %d S_ISSOCK.\n", argv[i], buf.st_mode);
        }
        else {
            printf("%s st_mod is %d error.\n", argv[i], buf.st_mode);
        }
    }
}

void test_access(int argc, char *argv[]) {
    for (int i = 1; i < argc; i++) {
        if (access(argv[i], F_OK) < 0) {
            printf("Don't have %s.\n", argv[i]);
            continue;
        }
        if (access(argv[i], R_OK | W_OK) < 0) {
            printf("%s don't have R_OK or W_OK.\n", argv[i]);
        }
        int fd = open(argv[i], O_RDWR);
        char buf[4096];
        ssize_t size = read(fd, buf, 4096);
        if (size > 0) {
            printf("%s.\n", buf);
        } else {
            printf("Read %s failed %ld.\n", argv[i], size);
        }
        close(fd);
    }
}

void test_umask() {
    mode_t mode = umask(0);
    printf("Old umask is %04o.\n", mode);
    if (creat("test_umask_1.txt", 0777) < 0) {
        printf("Creat file test_umask_1.txt failed.\n");
    }
    mode = umask(S_IRUSR | S_IRGRP | S_IROTH);
    printf("Old umask is %04o.\n", mode);
    if (creat("test_umask_2.txt", 0777) < 0) {
        printf("Creat file test_umask_1.txt failed.\n");
    }
    mode = umask(0);
    printf("Old umask is %04o.\n", mode);
}