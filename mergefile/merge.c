/* write a program to merge 2 files. EXAMPLE: if there are 2 files one with 100 lines and another file with 150 lines, create a file file_merge and that should have first 100 lines from file_1 and next 150 lines from file_2  */

// header file
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>

  
#define BUF_SIZE1 102400
#define BUF_SIZE2 102400
int main(int argc, char *argv[])
{
  int input_fd1,input_fd2,openFlag1,openFlag2,output_fd1;

  mode_t filePerm; //file permission mode_t set
  ssize_t readFile1,readFile2,writeFile1,writeFile2; //ssize_t signed size
  char buf1[BUF_SIZE1]; //set for first buffer size1, character buffer store the buffer size1
  char buf2[BUF_SIZE2]; //set for second buffer size2, character buffer store the buffer size2
  off_t goFile;  //off_t off set for using lseek
  
  openFlag1 = O_CREAT | O_RDONLY; //read only
  openFlag2 = O_CREAT | O_WRONLY; //write only
  filePerm = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH;//file permission giving
  int ret = EXIT_SUCCESS; //return the exit success

  //open the first input file for reading filepermission only giving
  //int open(const char *pathname, int flags, mode_t mode);
  input_fd1 = open(argv[1], openFlag1, filePerm);
  if(input_fd1 == -1)
  {
    ret = errno;
    perror("error opening the first input file1\n");
    goto close_exit;
  }

  //Read from the first input file
  //ssize_t read(int fd, void *buf, size_t count);
  readFile1 = read(input_fd1, buf1, BUF_SIZE1);
  if(readFile1 == -1)
  {
    ret = errno;
    perror("error opening the first readFile1\n");
    goto close_file;
  }

  //open the second input file for reading filepermission only giving
  //int open(const char *pathname, int flags, mode_t mode);
  input_fd2 = open(argv[2], openFlag1, filePerm);
  if(input_fd2 == -1)
  {
    ret = errno;
    perror("error opening the second input file2\n");
    goto close_file;
  }

  //open the first output file for writing filepermission only giving
  //int open(const char *pathname, int flags, mode_t mode);
  output_fd1 = open(argv[3],openFlag2,filePerm);
  if(output_fd1 == -1)
  {
    ret = errno;
    perror("error opening the  first output file1\n");
    goto close_file;
  }

  //write the first input file write from first output file
  //ssize_t write(int fd, const void *buf, size_t count);
  writeFile1 = write(output_fd1, buf1, readFile1);
  if(writeFile1 == -1)
  {
    ret = errno;
    perror("error opening the first writeFile1\n");
    goto close_file;
  }

  //lseek set from first intput file SEEK_SET  
  //off_t lseek(int fd, off_t offset, int whence);
  goFile = lseek(input_fd1, 0, SEEK_SET);
  if(goFile == -1)
  {
    ret = errno;
    perror("error opening the lseek goFile\n");
    goto close_file;
  }
  
  //read the second the input file from second readfile2 
  //ssize_t read(int fd, void *buf, size_t count);
  readFile2 = read(input_fd2, buf2, BUF_SIZE2);
  if(readFile2 == -1)
  {
    ret = errno;
    perror("error opening the second readFile2\n");
    goto close_file;
  }

  //write the second input file write from first output file
  //ssize_t write(int fd, const void *buf, size_t count);
  writeFile2 = write(output_fd1, buf2, readFile2);
  if(writeFile2 == -1)
  {
    ret = errno;
    perror("error opening the second writeFile2\n");
    goto close_file;
  }

close_file:
  close(input_fd1);
  close(input_fd2);
  close(output_fd1);
close_exit:
  close(-ret);
}
