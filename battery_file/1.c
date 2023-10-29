/*battery file*/

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

#define BUF_SIZE 512 
int main()
{
  int fd,openFlag,i,fd1;

  char buf[BUF_SIZE]; //character buffer size store
  ssize_t readFile;   //signed integer
  ssize_t writeFile;  //signed integer
  ssize_t writeCount; 
  char buf1[30]="battery percentage\n";

  openFlag = O_RDONLY; //O_RDONLY file read only;

  //battery file location path
  //int open(const char *pathname, int flags);
  fd = open("/sys/class/power_supply/BAT0/capacity", openFlag);

  if(fd == -1)
  {
    perror("error opening the file");
  }
  else
  {
    //read a file
    //ssize_t read(int fd, void *buf, size_t count);
    readFile = read(fd, buf, BUF_SIZE);
    if(readFile == -1)
    {
      perror("error opening the file");
    }

    //write a file
    //ssize_t write(int fd, const void *buf, size_t count);
    writeCount = write(1, buf1, strlen(buf1));
    writeFile = write(1,buf,readFile);
    if(writeFile == -1)
    {
      perror("erro opening the file");
    }
  }
  close(fd);
}

/* output 

   battery percentage
   37                   */
