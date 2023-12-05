/*Step1 - open a text file (read only), Step2 - read 20 bytes using pread(),and print 20 bytes with file position using lseek()
  Step3 - call dup2() by passing the a specific unused fd 
  Step4 - read 20 bytes using pread(),  and print 20 bytes with file position using lseek() */


#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>


#define BUF_SIZE 20 //20 bytes i givie for BUF_SIZE
//argc argument counter, argv argument vector character * pointer   
int main(int argc, char *argv[])
{
  int input_fd, dup2File;
  
  ssize_t readBytes, readBytes1; //ssize_t signed integer
  off_t cur_st1, cur_st2; //signed integer file offset
  char buf[BUF_SIZE]; //set for first buffer size1,character buf store the buffer size
  char buf1[BUF_SIZE];
  int ret_val = EXIT_SUCCESS;

  //step1 : the first open one file, that files as readonly permission
  //int open(const char *pathname, int flags);
  input_fd = open(argv[1], O_RDONLY);
  if(input_fd == -1)
  {
    ret_val = errno;
    perror("open : error open the input_fd");
    goto close_exit;
  }
  printf("old fd : %d\n",input_fd);

  //step2 : pread for input_fd, buf,buffer size give and the offset i give a 0,1 to 20 bytes only pread
  //ssize_t pread(int fd, void *buf, size_t count, off_t offset);
  readBytes = pread(input_fd, buf, BUF_SIZE, 0);
  if(readBytes == -1)
  {
    ret_val = errno;
    perror("pread : error open the readBytes");
    goto close_file;
  }
  printf("file point poistion : %ld\n%s\n",readBytes,buf);

  //lseek for input_fd inside 20 bytes after SEEK_CUR cursor set,20 bytes after only cursor start
  //off_t lseek(int fd, off_t offset, int whence);
  cur_st1 = lseek(input_fd, 20, SEEK_CUR);
  if(cur_st1 == -1)
  {
    ret_val = errno;
    perror("lseek : error open the cur_st1");
    goto close_file;
  }
  
  //step3 : dup2 for input_fd this for oldfd, 
  //newfd giving unused file descriptor for the new descriptor 4.
  //0 to 1023 totaly 1024, the already file open means 3 come.give the value above 4 to 1023 
  //int dup2(int oldfd, int newfd);
  dup2File = dup2(input_fd, 4);
  if(dup2File == -1)
  {
    ret_val = errno;
    perror("dup2 : error open the dup2File");
    goto close_file;
  }
  printf("dup2File : %d\n",dup2File);

  //step4 : pread for input_fd, buf,buffer size give and the offset i give a 0,1 to 20 bytes only pread
  //pread use for starting 1 to 20 bytes not go for 20 bytes after not take this pread.
  //ssize_t pread(int fd, void *buf, size_t count, off_t offset);
  readBytes1 = pread(dup2File, buf1, BUF_SIZE, 0);
  if(readBytes1 == -1)
  {
    ret_val = errno;
    perror("pread : error open the readBytes1");
    goto close_file;
  }

  //lseek for input_fd inside 20 bytes after SEEK_CUR cursor set,20 bytes after only cursor start
  //off_t lseek(int fd, off_t offset, int whence);
  cur_st2 = lseek(dup2File, 20, SEEK_CUR);
  if(cur_st2 == -1)
  {
    ret_val = errno;
    perror("lseek : error open the cur_st2");
    goto close_file;
  }
  printf("file point position : %ld\n%s\n",cur_st2,buf1);

  //close a file descriptor
  close_file:
    close(input_fd);
    close(dup2File);
  close_exit:
    close(-ret_val);
}
