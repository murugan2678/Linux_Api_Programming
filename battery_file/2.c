/* write a program for battery level using system call */

// header file
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define BUF_SIZE 512 
int main()
{
  int input_fd,openFlag,writeChar;

  char buf[BUF_SIZE]; //character buffer size store
  char buf1[30]="battery percentage\n"; //character buffer size store
  ssize_t readFile;   //ssize_t signed integer
  ssize_t writeFile,writeCount;  //ssize_t signed integer

  openFlag = O_RDONLY; //O_RDONLY file read only;
  int ret = EXIT_SUCCESS;
  
  //open a file, the first open a one file,this open file for read only
  //int open(const char *pathname, int flags);
  input_fd = open("/sys/class/power_supply/BAT0/capacity", openFlag);
  if(input_fd == -1)
  {
    ret = errno;
    perror("error opening the input file\n");
    goto close_exit;
  }

  //read a file, first open file inside read the open file
  //ssize_t read(int fd, void *buf, size_t count);
  readFile = read(input_fd, buf, BUF_SIZE);
  if(readFile == -1)
  {
    ret = errno;
    perror("error opening the readFile\n");
    goto close_file;
  }

  // write a file, inside characters store in strlen(buffer)
  // ssize_t write(int fd, const void *buf, size_t count);
  writeChar = write(1, buf1, strlen(buf1));
  if(writeChar == -1)
  {
    ret = errno;
    perror("error opening the writeChar\n");
    goto close_file;
  }

  // write a file, first open file write the read file 
  // ssize_t write(int fd, const void *buf, size_t count);
  writeFile = write(1,buf,readFile);
  if(writeFile == -1)
  {
    ret = errno;
    perror("erro opening the writeFile\n");
    goto close_file;
  }

close_file:
  close(input_fd);
close_exit:
  exit(-ret);
}

/* output

   battery percentage
   53                    */
