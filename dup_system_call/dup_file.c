/* write a program for Step1 - open a text file (read only).
   Step2 - read 20 bytes and print it. Step3 - call dup() by passing the fd from step1. Step4 - do step2 */

/****************************************************************/
/* Author          : Murugan M                                  */
/* Date            : 1/12/2023                                  */
/* file name       : dup_file                                   */
/* Description     : using system call for dup(),open(),read()  */
/****************************************************************/

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
  int input_fd, dupFile, openFlag;

  ssize_t readFile, readFile1; //ssize_t signed integer
  char buf[BUF_SIZE]; //buffer set for BUF_SIZE 
  char buf1[BUF_SIZE];
  int ret_val = EXIT_SUCCESS;

  openFlag = O_RDONLY; //file for readonly

  //first input_fd open inside giving for pathname passing argument 1,
  //openFlag this file for readonly
  //int open(const char *pathname, int flags);
  input_fd = open(argv[1], openFlag);
  if(input_fd == -1)
  {
    ret_val = errno;
    perror("open : error open the input_fd");
    goto close_exit;
  }
  printf("input_fd file descriptor : %d\n",input_fd);

  //read the file for input_fd, buffer set, BUF_SIZE count
  //read the first 20 bytes input_fd file read
  //ssize_t read(int fd, void *buf, size_t count);
  readFile = read(input_fd, buf, BUF_SIZE);
  if(readFile == -1)
  {
    ret_val = errno;
    perror("read : error open the readFile");
    goto close_file;
  }
  //input_fd file inside bytes only read, that print a bytes and character
  printf("read file for input_fd: %ld bytes\n%s\n",readFile,buf);

  //dup duplicate a file descriptor, inside oldfd for input_fd i giving
  //int dup(int oldfd);
  dupFile = dup(input_fd);
  if(dupFile == -1)
  {
    ret_val = errno;
    perror("dup : error open the dupFile");
    goto close_file;
  }
  printf("\nduplicate file descriptor : %d",dupFile);

  //dupFile for read the file, dup() this system call already dup inside oldfd given
  //oldfd file for input_fd file, dup for next 20 bytes only read for duplicate system call
  //read the file for dupFile, buffer1 set, BUF_SIZE count
  //ssize_t read(int fd, void *buf, size_t count);
  readFile1 = read(dupFile, buf1, BUF_SIZE);
  if(readFile1 == -1)
  {
    ret_val = errno;
    perror("read : error open the readFile1");
    goto close_file;
  }
  //here print the characters
  printf("%s\n",buf1);
  
  //close a file descriptor
  close_file:
   close(input_fd);
   close(dupFile);
  close_exit:
   close(-ret_val);
}
