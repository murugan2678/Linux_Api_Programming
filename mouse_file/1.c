/* mouse file */

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <linux/input.h>

int main()
{
  int input_fd,openFlag,i;
  
  ssize_t readFile;

  struct input_event rs; //set data type and variables
  struct timeval time; 
  unsigned short type;
  unsigned short code;
  unsigned int value;

  //flag set and read a file
  openFlag = O_RDONLY;
  int ret = EXIT_SUCCESS;

  //int open(const char *pathname, int flags);
  input_fd = open("/dev/input/event4", openFlag);  //event4
  if(input_fd == -1)
  {
    ret = errno;
    printf("error opening input file");
    goto close_exit;
  }
  else
  {
    while(1)
    {

      //ssize_t read(int fd, void *buf, size_t count);
      readFile = read(input_fd, &rs, sizeof(struct input_event));  //fd file describter,address sending,sizeof(intput) sending,read a file
      if(readFile == -1)
      {
	ret = errno;
	printf("error opening the first readFile1");
        goto close_file;
      }

      if(rs.code == 272)  //rs.code for 272 value for left click value
      {
	printf("left click\n");
      }
      if(rs.code == 273) //rs.code for 273 value for right click value
      {
	printf("right click\n");
      }
      if(rs.value == 1) //rs.value for 1 value for middle button value
      {
	printf("middle button\n"); 
      }
      printf("%d\n",rs.code);
    }
  }
close_file:
  close(input_fd);
close_exit:
  exit(-ret);
}
