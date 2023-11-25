//write a program for Open the file and read its contents,Count the number of lines in the file,
//Count the number of words in the file,Close the file after processing.

/************************************************************/
/* Author          : Murugan M                              */
/* Date            : 25/11/2023                             */
/* file name       : words_line                             */
/* Description     : using system call for open()and read() */
/************************************************************/

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

#define BUF_SIZE 512
int main(int argc,char *argv[]) //argc for arugment conuter,argv for arugment vector, character * pointer [] arrary
{
  int openFlag,input_fd,i,b,s;

  //ssize_t signed integer
  ssize_t readFile,writeFile;
  char buf[BUF_SIZE]; //character buf set for buffer size

  //mode_t mode set for filepermission
  mode_t filePerm;
  //openFlag set for O_CREAT, create a file
  openFlag = O_CREAT;
  int ret = EXIT_SUCCESS;

  //input open file pathname, flagset, file permission 
  //int open(const char *pathname, int flags, mode_t mode);
  input_fd = open(argv[1], openFlag, filePerm);
  if(input_fd == -1)
  {
    ret = errno;
    perror("error opening the input file");
    goto close_exit;
  }

  //read the input open file,buf set,buffer size set for count
  //ssize_t read(int fd, void *buf, size_t count);
  readFile = read(input_fd, buf, BUF_SIZE);
  if(readFile == -1)
  {
    ret = errno;
    perror("error opening the readFile");
    goto close_file;
  }
  b=0;
  s=0;
  for(i=0; i<readFile; i++)
  {
    if(buf[i] == 10)  //newline check, newline decimal value  10
    {
      b++;  //count the new line
    }
    else
    {
      s++;  //count the words
    }
  }
  printf("new line  : %d\n",b);
  printf("words     : %d\n",s);

//close a file descriptor
 close_file:
  close(input_fd);
 close_exit:
  close(-ret);
}
