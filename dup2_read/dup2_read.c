/* Step1 - open a text file (read only). Step2 - read 20 bytes and print it
   Step3 - call dup2() by passing the a specific unused fd.
   Step4 - do step2 Step5 */



#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>

#define BUF_SIZE 21
int main(int argc, char *argv[])
{
  int input_fd,dupFile;
  ssize_t readBytes1,readBytes2;
  char buf[BUF_SIZE];
  int ret_val = EXIT_SUCCESS;

  //Step1 - open a text file (read only)
  //int open(const char *pathname, int flags);
  input_fd = open(argv[1], O_RDONLY);
  if(input_fd == -1)
  {
    ret_val = errno;
    perror("open : error opening the input_fd");
    goto close_exit;
  }
  
  //Step2 - read 20 bytes and print it 
  //ssize_t read(int fd, void *buf, size_t count);
  readBytes1 = read(input_fd, buf, BUF_SIZE-1);
  if(readBytes1 == -1)
  {
    ret_val = errno;
    perror("read : error opening the readBytes1");
    goto close_file;
  }
  printf("readBytes1 : %s\n%ld bytes\n",buf,readBytes1);

  //Step3 - call dup2() by passing the a specific unused fd
  //int dup2(int oldfd, int newfd);
  dupFile = dup2(input_fd, 4);
  if(dupFile == -1)
  {
    ret_val = errno;
    perror("dup2 : error opening the dupFile");
    goto close_file;
  }

  //Step4 - do step2 read 20 bytes and print it 
  //ssize_t read(int fd, void *buf, size_t count);
  readBytes2 = read(input_fd, buf, BUF_SIZE-1);
  if(readBytes2 == -1)
  {
    ret_val = errno;
    perror("read : error opening the readBytes2");
    goto close_2files;
  }
  printf("readBytes2 : %s\n%ld bytes\n",buf,readBytes2);
  exit(EXIT_SUCCESS);

 close_2files:
   close(dupFile);  //step2 clean up
 close_file:
   close(input_fd); //step1 clean up
 close_exit:
   close(ret_val);
}
