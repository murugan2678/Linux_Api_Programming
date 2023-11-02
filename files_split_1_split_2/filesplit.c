/* Task 1: write a program to split a file into 2 half. 
   Example - if file_a has 250 lines, create 2 files by name split_1 and split_2. Those files should have 125 lines each */

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h> 

#define BUF_SIZE 102400 //buffer size set
int main(int argc, char *argv[]) 
{
  int fd,createFile1,createFile2,openFlag,b,j,i,number,b1;
  
  mode_t filePerm; //file permission mode_t set
  mode_t filePerm1;
  mode_t filePerm2;
  
  off_t goFile;
  openFlag = O_CREAT | O_RDONLY;  //create file that file read only
  char buf[BUF_SIZE];
  char buf1[BUF_SIZE];
  ssize_t readFile,readFile1,writeFile1,writeFile2;
  int bytes;

  filePerm = S_IRUSR | S_IWUSR | S_IRGRP | S_IRGRP | S_IROTH;  //first file permission
  filePerm1 = S_IRUSR | S_IWUSR | S_IRGRP | S_IRGRP | S_IROTH; //second file permission
  filePerm2 = S_IRUSR | S_IWUSR | S_IRGRP | S_IRGRP | S_IROTH; //thrid file permission
  
  //int open(const char *pathname, int flags, mode_t mode);
  fd = open(argv[1], openFlag, filePerm); //one file open
  if(fd == -1)
  {
    perror("error opening the file");
  }

  //ssize_t read(int fd, void *buf, size_t count);
  readFile = read(fd, buf, BUF_SIZE); //first open file read
  if(readFile == -1)
  {
    perror("error opening the file");
  }

  b=0;
  for(j=0;j<readFile;j++)
  {
    if(buf[j]==10)
    {
      b++;  //newline count
    }
  }
  number=b/2; //file lines divided
  printf("%d",number);
  b1=0;
  bytes;
  for(j=0;j<readFile;j++)
  {
    bytes++;  //count the characters bytes
    if(buf[j]==10)
    {
      b1++;
    }
    if(b1==number) //check the newline and divide the value 
    {
      break;
    }
  }
  
  //int creat(const char *pathname, mode_t mode);
  createFile1 = creat(argv[2], filePerm1); //create the first file
  if(createFile1 == -1)
  {
    perror("error opening the file");
  }

  //ssize_t write(int fd, const void *buf, size_t count);
  writeFile1 = write(createFile1, buf, bytes); //first create file write

  //off_t lseek(int fd, off_t offset, int whence); 
  goFile = lseek(fd, bytes, SEEK_SET);   //lseek set start of a file

  //off_t lseek(int fd, off_t offset, int whence);
  readFile = read(fd, buf1, BUF_SIZE);  //read openfile bytes store the buffer size

  //int creat(const char *pathname, mode_t mode);
  createFile2 = creat(argv[3], filePerm2); //create the second file 
  if(createFile2 == -1)
  {
    perror("error opening the file");
  }

  //ssize_t write(int fd, const void *buf, size_t count);
  writeFile2 = write(createFile2, buf1, readFile); //second create file write
  close(fd);
  close(createFile1);
  close(createFile2); 
}
