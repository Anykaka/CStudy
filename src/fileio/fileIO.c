#include "fileIO.h"

int FIOrun(){
    char* filename = "fileIO.txt";
    int fd = OpenFile(filename);

    // fcntl函数
    test_fcntl(fd, filename);
    test_1(fd, filename);

    close(fd);
}

int OpenFile(char* filename){
    // 打开文件（如果没有就添加一个新的文件）
    int fd = open(filename, O_RDWR);
    if (FILE_ERR != fd) {
        DPRINT("-----> Open file %s %d sucess.", filename, fd);
    }
    else {
        fd = creat(filename, S_IRUSR | S_IWUSR);   // 等效于open(filename, O_WRONLY | O_CREAT | O_TRUNC, mode);
        DPRINT("-----> Add file %s sucess.", filename);
    }
    return fd;
}

int test_1(int fd, char* filename) {
    // 设置偏移量
    off_t offset = 60;
    off_t seek_r = lseek(fd, offset, SEEK_SET);    // SEEK_SET、SEEK_CUR、SEEK_END:分别是设置偏移量、设置相对偏移量、从末尾设置偏移量
    if (FILE_ERR == seek_r){
        DPRINT("-----> file:%s can't set seek.", filename);
    }
    else {
        DPRINT("-----> file:%s set seek sucess.", filename);
    }

    char buf[] = "test something";
    // 读写
    int write_r = write(fd, buf, sizeof(buf));
    if (sizeof(buf) == write_r) {
        DPRINT("-----> file:%s write sucess.", filename);
    }
    else {
        DPRINT("-----> file:%s write failed, write_r is %d, but buf is %ld.", filename, write_r, sizeof(buf));
    }

    char rev_buf[sizeof(buf)];
    lseek(fd, offset, SEEK_SET);
    ssize_t size = read(fd, rev_buf, sizeof(buf));
    DPRINT("%s %ld\n", rev_buf, size);

    // 原子读写
    write_r = pwrite(fd, buf, sizeof(buf), offset);
    if (sizeof(buf) == write_r) {
        DPRINT("-----> file:%s write sucess.", filename);
    }
    else {
        DPRINT("-----> file:%s write failed, write_r is %d, but buf is %ld.", filename, write_r, sizeof(buf));
    }

    size = pread(fd, rev_buf, sizeof(buf), offset);
    DPRINT("%s %ld\n", rev_buf, size);

    // 同步读写
    fsync(fd);

    // dup、dup2
    int fd_dup = dup(fd);
    rev_buf[0] = 0;
    DPRINT("%d %s\n", fd_dup, rev_buf);
    size = pread(fd_dup, rev_buf, sizeof(buf), offset);
    DPRINT("%d %s %ld\n", fd_dup, rev_buf, size);

    fd_dup = 5;
    dup2(fd, fd_dup);
    rev_buf[0] = 0;
    DPRINT("%d %s\n", fd_dup, rev_buf);
    size = pread(fd_dup, rev_buf, sizeof(buf), offset);
    DPRINT("%d %s %ld\n", fd_dup, rev_buf, size);
}

int test_fcntl(int fd, char* filename) {
    // 打印文件描述符的文件标志说明
    int fl = fcntl(fd, F_GETFL);
    DPRINT("%x.", fl);
    fcntl(fd, F_SETFL, fl | O_SYNC);
    fl = fcntl(fd, F_GETFL);
    DPRINT("%x.", fl);
}

// 与dup2函数功能相同的函数，要求不调用fcntl，有正确的出错处理
void sercises_3_2(int fd1, int fd2){
    fd1 = open("sercises_3_2_fd1.txt", O_RDWR | O_SYNC | O_CREAT, 0777);
    fd2 = open("sercises_3_2_fd2.txt", O_RDWR | O_SYNC | O_CREAT, 0777);
    #if 1
    if (fd1 == fd2) {
        goto WRITE;
    }
    while (1)
    {
        close(fd2);
        if (fd2 == dup(fd1))
            goto WRITE;
        DPRINT("%s:%d fd1:%d and fd2:%d.",fd1, fd2);
        close(fd2);
    }
    #endif

WRITE:{
    DPRINT("%s:%d fd1:%d and fd2:%d.",fd1, fd2);
    ssize_t size = write(fd2, "fd2test", sizeof("fd2test"));
    if (sizeof("fd2test") != size) {
        DPRINT("%s:%d fd:%d write fd2test failed.",fd2);
    }
    close(fd2);
    close(fd1);
}
    
}

void sercises_3_6() {
    int fd = open("sercises_3_6.txt", O_RDWR | O_SYNC | O_CREAT | O_APPEND, 0777);
    ssize_t size = write(fd, "write_1__", 10);
    if (10 != size) {
        DPRINT("%s:%d fd:%d write write_1__ failed.",fd);
    }
    // 结果：文件尾端添加
    off_t off_seek = 100;
    lseek(fd, off_seek, SEEK_SET);
    size = write(fd, "write_2__", 10);
    if (10 != size) {
        DPRINT("%s:%d fd:%d write write_2__ failed.",fd);
    }
    // 结果：文件尾端添加
    size = pwrite(fd, "write_3__", 10, off_seek);
    if (10 != size) {
        DPRINT("%s:%d fd:%d write write_3__ failed.",fd);
    }
    close(fd);
}
