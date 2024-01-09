// Write a program to provide required permissions to the files and directories created in assignment 15

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>

#define BUF_SIZE 59 //.vimrc file size
#define BUF_SIZE1 3848 //.bashrc file size
int main(int argc, char *argv[])
{
  int x,y,i=0,sum=0,oct,ch_file,mk1_file,mk2_file,input_fd1,input_fd2,output_fd1,output_fd2;

  ssize_t readFile1,readFile2,writeFile1,writeFile2; //ssize_t signed integer
  char buf[BUF_SIZE];  //buffer size for .vimrc file
  char buf1[BUF_SIZE1]; //buffer size1 for .bashrc file 
  int ret_val = EXIT_SUCCESS;

  int arr[8] = {00,01,02,03,04,05,06,07};
  
  //step1 : convert a string to an integer
  //int atoi(const char *nptr);
  x=atoi(argv[1]);
 
  //step2 : decimal to octal convert the value
  while(x>0)
  {
    y=x%10;
    x=x/10;
    if(y>=0&&y<=7) //octal for 0to7
    {
      oct = arr[y]<<i;
    }
    sum=sum+oct;
    i=i+3;
  }
  
  //stpe3 : mkdir create the directory for Home directory
  //int mkdir(const char *pathname, mode_t mode);
  mk1_file = mkdir(argv[2], sum);
  if(mk1_file == -1)
  {
    ret_val = errno;
    perror("mkdir : error opening the mk1_file");
    goto close_exit;
  }
  
  //step4 : chdir change the directory for Home directory
  //int chdir(const char *path);
  ch_file = chdir("Home");
  if(ch_file == -1)
  {
    ret_val = errno;
    perror("chdir : error opning the ch_file");
    goto close_exit;
  }

  //step5 : mkdir create the Home directory templates for Desktop,Documents,Downloads,Music,Videos,Pictures,Templates
  for(i=3; i<argc; i++)
  {
    //int mkdir(const char *pathname, mode_t mode);
    mk2_file = mkdir(argv[i], sum);
    if(mk2_file == -1)
    {
      ret_val = errno;
      perror("mkdir : error opening the mk2_file");
      goto close_exit;
    }
  }

  //step6 : open the .vimrc file location and that files as read only
  //int open(const char *pathname, int flags);
  input_fd1 = open("/home/murugan/.vimrc", O_RDONLY);
  if(input_fd1 == -1)
  {
    ret_val = errno;
    perror("open : error opening the input_fd1");
    goto close_exit;
  }
  
  //step7 : open the .vimrc that files creat a file as read and write,
  //the file permission for user,group,other a read only
  //int open(const char *pathname, int flags, mode_t mode);
  output_fd1 = open(".vimrc", O_CREAT | O_RDWR, 0444);
  if(output_fd1 == -1)
  {
    ret_val = errno;
    perror("open : error opening the output_fd1");
    goto close_file;
  }
  
  //step8 : read the file input_fd1 file buf and buffer size set
  //ssize_t read(int fd, void *buf, size_t count);
  readFile1 = read(input_fd1, buf, BUF_SIZE-1);
  if(readFile1 == -1)
  {
    ret_val = errno;
    perror("read : error opening the readFile1");
    goto close_2files;
  }
  
  //step9 : write the file for output_fd1 buf and buffer size set
  //ssize_t write(int fd, const void *buf, size_t count);
  writeFile1 = write(output_fd1, buf, BUF_SIZE-1);
  if(writeFile1 == -1)
  {
    ret_val = errno;
    perror("write : error openig the writeFile1");
    goto close_2files;
  }
  
  //step10 : open the .bashrc file location and that files as read only
  //int open(const char *pathname, int flags);
  input_fd2 = open("/home/murugan/.bashrc",O_RDONLY);
  if(input_fd2 == -1)
  {
    ret_val = errno;
    perror("open : error opening the input_fd2");
    goto close_2files;
  }
 
  //step11 : open the .bashrc that files creat a file as read and write,
  //the file permission for user,group,other a read only
  //int open(const char *pathname, int flags, mode_t mode);
  output_fd2 = open(".bashrc", O_CREAT | O_RDWR, 0444);
  if(output_fd2 == -1)
  {
    ret_val = errno;
    perror("open : error opening the output_fd2");
    goto close_3files;
  }

  //step12 : read the file input_fd1 file buf and buffer size set
  //ssize_t read(int fd, void *buf, size_t count);
  readFile2 = read(input_fd2, buf1, BUF_SIZE1-1);
  if(readFile2 == -1)
  {
    ret_val = errno;
    perror("read : error opening the readFile2");
    goto close_4files;
  }

  //step13 : write the file for output_fd1 buf and buffer size set
  //ssize_t write(int fd, const void *buf, size_t count);
  writeFile2 = write(output_fd2, buf1, BUF_SIZE1-1);
  if(writeFile2 == -1)
  {
    ret_val = errno;
    perror("write : error opening the writeFile2");
    goto close_4files;
  }
  exit(EXIT_SUCCESS);
  
  //step14 : close file descripator fd1 and fd2
  close_4files:
    close(output_fd2);
  close_3files:
    close(input_fd2);
  close_2files:
    close(output_fd1);
  close_file:
    close(input_fd1);
  close_exit:
    exit(ret_val);
}
