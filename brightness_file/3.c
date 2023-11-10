/* write a program brightness level using  */

// header file
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

#define BUF_SIZE 512
#define brightpath "/sys/class/backlight/intel_backlight/brightness"
int main()
{
  int input_fd,openFlag;
 
  ssize_t readFile;   //ssize_t signed integer
  char buf[BUF_SIZE]; //character buffer size store
  ssize_t writeChar,writeFile;  //ssize_t signed integer
  char buf1[15] = {"brightness\n"}; //character buffer size store

  openFlag = O_RDONLY; //O_RDONLY file read only;
  int ret = EXIT_SUCCESS;
  //open a file, the first open a one file, add the brigtness path, this open file for read only
  //int open(const char *pathname, int flags);
  input_fd = open(brightpath, openFlag);
  if(input_fd == -1)
  {
    ret = errno;
    perror("error opening the input file\n");
    goto close_exit;
  }

  //read file, the open_fd file read the file
  //ssize_t read(int fd, void *buf, size_t count);
  readFile = read(input_fd, buf, BUF_SIZE);
  if(readFile == -1)
  {
    ret = errno;
    perror("error opening the readFile\n");
    goto close_file;
  }
     link
  //write file, write the buffer inside character write
  //ssize_t write(int fd, const void *buf, size_t count);
  writeChar = write(1, buf1, strlen(buf1));
  if(writeChar == -1)
  {
    ret = errno;
    perror("error opening the writeChar\n");
    goto close_file;
  }

  //write file, write file for read the file
  //ssize_t write(int fd, const void *buf, size_t count);
  writeFile = write(1, buf, readFile);
  if(writeFile == -1)
  {
    ret = errno;
    perror("error opening the writeFile\n");
    goto close_file;
  }

close_file:
  close(input_fd);
close_exit:
  exit(-ret);
}

/* output

   brightness
   1018               */
