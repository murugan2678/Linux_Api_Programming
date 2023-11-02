/* write a program to merge 2 files. EXAMPLE: if there are 2 files one with 100 lines and another file with 150 lines, create a file file_merge and that should have first 100 lines from file_1 and next 150 lines from file_2  */

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>

  
#define BUF_SIZE 102400
#define BUF_SIZE1 102400
int main(int argc, char *argv[])
{
  int fd1,openFlag,fd2,fd3,createFile;

  mode_t filePerm;
  ssize_t readFile,readFile1,writeFile,writeFile1;
  char buf[BUF_SIZE];
  char buf1[BUF_SIZE1];
  off_t goFile;
  openFlag = O_CREAT | O_RDONLY;
  
  filePerm = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH;

  //int open(const char *pathname, int flags, mode_t mode);
  fd1 = open(argv[1], openFlag, filePerm);
  if(fd1 == -1)
  {
    perror("error opening the first open file\n");
  }

  //ssize_t read(int fd, void *buf, size_t count);
  readFile = read(fd1, buf, BUF_SIZE);

  //int open(const char *pathname, int flags, mode_t mode);
  fd2 = open(argv[2], openFlag, filePerm);
  if(fd2 == -1)
  {
    perror("error opening the second open file\n");
  }

  //int creat(const char *pathname, mode_t mode);
  createFile = creat(argv[3],filePerm);
  if(createFile == -1)
  {
    perror("error opening the create file\n");
  }

  //ssize_t write(int fd, const void *buf, size_t count);
  writeFile = write(createFile, buf, readFile);

  //off_t lseek(int fd, off_t offset, int whence);
  goFile = lseek(fd1,0,SEEK_SET);

  //ssize_t read(int fd, void *buf, size_t count);
  readFile1 = read(fd2, buf1, BUF_SIZE1);

  //ssize_t write(int fd, const void *buf, size_t count);
  writeFile1 = write(createFile, buf1, readFile1);

  close(fd1);
  close(fd2);
  close(fd3);
}
