#include "../include/fileIO.h"

int FIOrun(){
    char* filename = "fileIO.txt";
    int fd = OpenFile(filename);

    test_1(fd, filename);
    // fcntl函数
    test_fcntl(fd, filename);

    close(fd);
}

int OpenFile(char* filename){
    // 打开文件（如果没有就添加一个新的文件）
    int fd = open(filename, O_RDWR | O_SYNC);
    if (FILE_ERR != fd) {
        printf("-----> Open file %s %d sucess.\n", filename, fd);
    }
    else {
        fd = creat(filename, S_IRUSR | S_IWUSR);   // 等效于open(filename, O_WRONLY | O_CREAT | O_TRUNC, mode);
        printf("-----> Add file %s sucess.\n", filename);
    }
    return fd;
}

int test_1(int fd, char* filename) {
    // 设置偏移量
    off_t offset = 60;
    off_t seek_r = lseek(fd, offset, SEEK_SET);    // SEEK_SET、SEEK_CUR、SEEK_END:分别是设置偏移量、设置相对偏移量、从末尾设置偏移量
    if (FILE_ERR == seek_r){
        printf("-----> file:%s can't set seek.\n", filename);
    }
    else {
        printf("-----> file:%s set seek sucess.\n", filename);
    }

    char buf[] = "test something";
    // 读写
    int write_r = write(fd, buf, sizeof(buf));
    if (sizeof(buf) == write_r) {
        printf("-----> file:%s write sucess.\n", filename);
    }
    else {
        printf("-----> file:%s write failed, write_r is %d, but buf is %ld.\n", filename, write_r, sizeof(buf));
    }

    char rev_buf[sizeof(buf)];
    lseek(fd, offset, SEEK_SET);
    read(fd, rev_buf, sizeof(buf));
    printf("%s\n", rev_buf);

    // 原子读写
    write_r = pwrite(fd, buf, sizeof(buf), offset);
    if (sizeof(buf) == write_r) {
        printf("-----> file:%s write sucess.\n", filename);
    }
    else {
        printf("-----> file:%s write failed, write_r is %d, but buf is %ld.\n", filename, write_r, sizeof(buf));
    }

    pread(fd, rev_buf, sizeof(buf), offset);
    printf("%s\n", rev_buf);

    // 同步读写
    fsync(fd);

    // dup、dup2
    int fd_dup = dup(fd);
    rev_buf[0] = 0;
    printf("%d %s\n", fd_dup, rev_buf);
    pread(fd_dup, rev_buf, sizeof(buf), offset);
    printf("%d %s\n", fd_dup, rev_buf);

    fd_dup = 5;
    dup2(fd, fd_dup);
    rev_buf[0] = 0;
    printf("%d %s\n", fd_dup, rev_buf);
    pread(fd_dup, rev_buf, sizeof(buf), offset);
    printf("%d %s\n", fd_dup, rev_buf);
}

int test_fcntl(int fd, char* filename) {
    // 打印文件描述符的文件标志说明
    int fl = fcntl(fd, F_GETFL);
    
}