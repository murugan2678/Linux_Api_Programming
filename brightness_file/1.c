/* brightness */

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

#define BUF_SIZE 512
//brightness file location path
#define bright "/sys/class/backlight/intel_backlight/brightness"
int main()
{
  int fd,openFlag;
 
  ssize_t readFile;   //signed integer
  char buf[BUF_SIZE]; //character buffer size store

  ssize_t writeCount,writeFile;
  char buf1[15] = {"brightness :"};

  openFlag = O_RDONLY; //O_RDONLY file read only;

  //int open(const char *pathname, int flags);
  fd = open(bright, openFlag);

  if(fd == -1)
  {
    perror("error opening the file");
  }
  else
  {
    //read file
    //ssize_t read(int fd, void *buf, size_t count);
    readFile = read(fd, buf, BUF_SIZE);
    if(readFile == -1)
    {
      perror("error opening the file");
    }
    
    //write file
    //ssize_t write(int fd, const void *buf, size_t count);
    writeFile = write(1, buf1, strlen(buf1));
    writeCount = write(1, buf, readFile);
    if(writeCount == -1)
    {
      perror("error opening the file");
    }
  }
  close(fd);
}

/* output

   brightness :780  */
