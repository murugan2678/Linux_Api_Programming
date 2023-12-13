/* Step1 - open a text file (read only)
   Step2 - read 20 bytes using pread()and print 20 bytes with file position using lseek()
   Step3 - call dup() by passing the fd from step1
   Step4 - read 20 bytes using pread(),and print 20 bytes with file position using lseek() */


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
  int input_fd,dup_file;
  off_t goFile1,goFile2;
  ssize_t readBytes1,readBytes2;
  char buf[BUF_SIZE];
  char buf1[BUF_SIZE];
  int ret_val = EXIT_SUCCESS;

  //Step1 - open a text file (read only)
  input_fd = open(argv[1], O_RDONLY);
  if(input_fd == -1)
  {
    ret_val = errno;
    perror("open : error opening the input_fd");
    goto close_exit;
  }
 
  //Step2 - read 20 bytes using pread(),and print 20 bytes with file position using lseek()
  //ssize_t pread(int fd, void *buf, size_t count, off_t offset);
  readBytes1 = pread(input_fd, buf, BUF_SIZE-1, 0); 
  if(readBytes1 == -1)
  {
    ret_val = errno;
    perror("pread : error opening the readBytes1");
    goto close_file;
  }
  printf("file point poistion : %ld\n%s\n",readBytes1,buf);

  //off_t lseek(int fd, off_t offset, int whence);
  goFile1 = lseek(input_fd, BUF_SIZE-1, SEEK_CUR);
  if(goFile1 == -1)
  {
    ret_val = errno;
    perror("lseek : error opening the goFile");
    goto close_file;
  }

  //Step3 - call dup() by passing the fd from step1
  //int dup(int oldfd);
  dup_file = dup(input_fd);
  if(dup_file == -1)
  {
    ret_val = errno;
    perror("dup : error opening the dup_file");
    goto close_file;
  }

  //Step4 -read 20 bytes using pread(),and print 20 bytes with file position using lseek().
  //ssize_t pread(int fd, void *buf, size_t count, off_t offset);
  readBytes2 = pread(input_fd, buf1, BUF_SIZE-1, 0); 
  if(readBytes2 == -1)
  {
    ret_val = errno;
    perror("pread : error opening the readBytes2");
    goto close_2files;
  }

  //off_t lseek(int fd, off_t offset, int whence);
  goFile2 = lseek(dup_file, BUF_SIZE-1, SEEK_CUR);
  if(goFile2 == -1)
  {
    ret_val = errno;
    perror("lseek : error opening the goFile2");
    goto close_2files;
  }
  printf("file point position : %ld\n%s\n",goFile2,buf1);
  exit(EXIT_SUCCESS);

 close_2files:
   close(dup_file); //step2 clean up
 close_file:
   close(input_fd); //step1 clean up
 close_exit:
   exit(ret_val);
}
