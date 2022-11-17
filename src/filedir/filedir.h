#pragma FILE_AND_DIR
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

void dumpstat(int argc, char *argv[]);
void test_access(int argc, char *argv[]);
void test_umask();
