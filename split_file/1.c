/* Task 1: write a program to split a file into 2 half. 
   Example - if file_a has 250 lines, create 2 files by name split_1 and split_2. Those files should have 125 lines each */


// header file
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h> 
#include <stdlib.h>
#include <stdio.h>

#define BUF_SIZE 102400 //buffer size set
int main(int argc, char *argv[]) 
{
  int input_fd,output_fd1,output_fd2,openFlag1,openFlag2,b,j,i,number,b1;
  
  mode_t filePerm1; //file permission mode_t set
  mode_t filePerm2;
  mode_t filePerm3;
  
  off_t goFile;
  openFlag1 = O_CREAT | O_RDONLY;  //file1 for read only
  openFlag2 = O_CREAT | O_WRONLY;  //file2 for write only
  char buf[BUF_SIZE]; 
  char buf1[BUF_SIZE];
  ssize_t readFile1,readFile2,writeFile1,writeFile2; //ssize_t signed size
  int bytes;

  filePerm1 = S_IRUSR | S_IWUSR | S_IRGRP | S_IRGRP | S_IROTH;  //first file permission
  filePerm2 = S_IRUSR | S_IWUSR | S_IRGRP | S_IRGRP | S_IROTH; //second file permission1
  filePerm3 = S_IRUSR | S_IWUSR | S_IRGRP | S_IRGRP | S_IROTH; //thrid file permission2
  
  int ret = EXIT_SUCCESS;
  //open the input file for reading
  //int open(const char *pathname, int flags, mode_t mode);
  input_fd = open(argv[1], openFlag1, filePerm1); //one file open
  if(input_fd == -1)
  {
    ret = errno;
    perror("error opening input file");
    goto close_exit;
  }

  // Read from the input file 
  //ssize_t read(int fd, void *buf, size_t count);
  readFile1 = read(input_fd, buf, BUF_SIZE); //first open file read
  if(readFile1 == -1)
  {
    ret = errno;
    perror("error opening the first readFile1");
    goto close_file;
  }

  b=0;
  for(j=0; j<readFile1; j++)
  {
    if(buf[j]==10)
    {
      b++;  //newline count
    }
  }
  number=b/2; //file lines divided
  //printf("%d",number);
  b1=0;
  bytes;
  for(j=0; j<readFile1; j++)
  {
    bytes++;  //count the characters bytes
    if(buf[j] == 10)
    {
      b1++; //newline count
    }
    if(b1 == number) //check the newline and divide the value 
    {
      break;
    }
  }
  
  //open the output file for writing
  //int open(const char *pathname, int flags, mode_t mode);
  output_fd1 = open(argv[2],openFlag2,filePerm2);
  if(output_fd1 == -1)
  {
    ret = errno;
    perror("error opening the first output file1");
    goto close_file;
  }

  //write the first output_fd1 file writting
  //ssize_t write(int fd, const void *buf, size_t count);
  writeFile1 = write(output_fd1, buf, bytes); //first create file write
  if(writeFile1 == -1)
  {
    ret = errno;
    perror("error opening the first writeFile1");
    goto close_file;
  }
 
  //lseek the input_fd file bytes counts,SEEK_SET
  //off_t lseek(int fd, off_t offset, int whence); 
  goFile = lseek(input_fd, bytes, SEEK_SET);   //lseek set start of a file
  if(goFile == -1)
  {
    ret = errno;
    perror("error opening the lseek goFile");
    goto close_file;
  }

  //read the input_fd file,buffer set, buffer size for input file
  //ssize_t read(int fd, void *buf, size_t count);
  readFile2 = read(input_fd, buf1, BUF_SIZE);  //read openfile bytes store the buffer size
  if(readFile2 == -1)
  {
    ret = errno;
    perror("error opening the second readFile2");
    goto close_file;
  }

  //open the second output file for writing
  //int open(const char *pathname, int flags, mode_t mode);
  output_fd2 = open(argv[3],openFlag2,filePerm3);
  if(output_fd2 == -1)
  {
    ret = errno;
    perror("error opening the second output file2");
    goto close_file;
  }

  //write the second output_fd2 file writting
  //ssize_t write(int fd, const void *buf, size_t count);
  writeFile2 = write(output_fd2, buf1, readFile2); //second create file write
  if(writeFile2 == -1)
  {
    ret = errno;
    perror("error opening the second writeFile2");
    goto close_file;
  }
close_file:
  close(input_fd);
  close(output_fd1);
  close(output_fd2);
close_exit:
  exit(-ret);
}
