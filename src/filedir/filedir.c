#include "filedir.h"

void dumpstat(int argc, char *argv[]) {
    struct stat buf;
    
    for (int i = 1; i < argc; i++) {
        DPRINT("arg[%d] is : %s.", i, argv[i]);
        if (stat(argv[i], &buf) < 0) {
            DPRINT("Get %s stat err.", argv[i]);
            continue;
        }
        if (S_ISREG(buf.st_mode)) {
            DPRINT("%s st_mod is %d S_ISREG.", argv[i], buf.st_mode);
        }
        else if (S_ISBLK(buf.st_mode)) {
            DPRINT("%s st_mod is %d S_ISBLK.", argv[i], buf.st_mode);
        }
        else if (S_ISCHR(buf.st_mode)) {
            DPRINT("%s st_mod is %d S_ISCHR.", argv[i], buf.st_mode);
        }
        else if (S_ISDIR(buf.st_mode)) {
            DPRINT("%s st_mod is %d S_ISDIR.", argv[i], buf.st_mode);
        }
        else if (S_ISFIFO(buf.st_mode)) {
            DPRINT("%s st_mod is %d S_ISFIFO.", argv[i], buf.st_mode);
        }
        else if (S_ISLNK(buf.st_mode)) {
            DPRINT("%s st_mod is %d S_ISLNK.", argv[i], buf.st_mode);
        }
        else if (S_ISSOCK(buf.st_mode)) {
            DPRINT("%s st_mod is %d S_ISSOCK.", argv[i], buf.st_mode);
        }
        else {
            DPRINT("%s st_mod is %d error.", argv[i], buf.st_mode);
        }
    }
}

void test_access(int argc, char *argv[]) {
    for (int i = 1; i < argc; i++) {
        if (access(argv[i], F_OK) < 0) {
            DPRINT("Don't have %s.", argv[i]);
            continue;
        }
        if (access(argv[i], R_OK | W_OK) < 0) {
            DPRINT("%s don't have R_OK or W_OK.", argv[i]);
        }
        int fd = open(argv[i], O_RDWR);
        char buf[4096];
        ssize_t size = read(fd, buf, 4096);
        if (size > 0) {
            DPRINT("%s.", buf);
        } else {
            DPRINT("Read %s failed %ld.", argv[i], size);
        }
        close(fd);
    }
}

void test_umask() {
    mode_t mode = umask(0);
    DPRINT("Old umask is %04o.", mode);
    if (creat("test_umask_1.txt", 0777) < 0) {
        DPRINT("Creat file test_umask_1.txt failed.")
    }
    mode = umask(S_IRUSR | S_IRGRP | S_IROTH);
    DPRINT("Old umask is %04o.", mode);
    if (creat("test_umask_2.txt", 0777) < 0) {
        DPRINT("Creat file test_umask_1.txt failed.");
    }
    mode = umask(0);
    DPRINT("Old umask is %04o. failed", mode)
}