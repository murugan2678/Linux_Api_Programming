/* Task 3: write a program to take the line numbers which are multiples of 10. 
   Example - source_file has 100 lines,
   you have to create a file file_10th and save line numbers 10, 20, 30, 40, ... 100  */

//header file
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>

#define BUF_SIZE 102400
int main(int argc, char *argv[]) //argc argument counter, argv argument vector
{
  int input_fd,openFlag,openFlag1,output_fd1,i,k,b,y,m,d,s=0;
  int num,bytes,file,sum=1,bytes1;
  mode_t filePerm;   //mode_t file mode set
  off_t goFile,goFile1; //signed integer file offset
  char buf[BUF_SIZE];  //set for first buffer size1,character buffer store the buffer size
  char buf1[BUF_SIZE];  //set for second buffer size
  ssize_t readFile,readFile1,writeFile;  
  openFlag  = O_CREAT | O_RDONLY; //create file that file as readonly
  openFlag1 = O_CREAT | O_WRONLY; //create file that file as writeonly

  filePerm = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH; //file permission
  int ret = EXIT_SUCCESS;

  //open the first input file for reading filepermission only giving
  //int open(const char *pathname, int flags, mode_t mode);
  input_fd = open(argv[1], openFlag, filePerm);
  if(input_fd == -1)
  {
    ret = errno;
    perror("error opening the file input file\n");
    goto close_exit;
  }

  //open the first output file for writing filepermission only giving
  //int creat(const char *pathname, mode_t mode);
  output_fd1 = open(argv[2], openFlag1, filePerm);
  if(output_fd1 == -1)
  {
    ret = errno;
    perror("error opening the output file\n");
    goto close_file;
  }
  
  b=0;
  //read from the first input file
  //ssize_t read(int fd, void *buf, size_t count);
  readFile = read(input_fd, buf, BUF_SIZE);
  if(readFile == -1)
  {
    ret = errno;
    perror("error opening the first readFile\n");
    goto close_file;
  }
  //int atoi(const char *nptr);
  num=atoi(argv[3]); //convert a string to an integer
  for(i=0;i<readFile;i++)
  {
    bytes++; //bytes count
    if(buf[i]==10) //newline checking
    {
      b++;   //newline count
    }
    file=(num*sum)-1;  //input values here multiplication
    if(b==file)  //here checking newline and input values
    {
      //lseek set inupt file SEEK_SET
      //off_t lseek(int fd, off_t offset, int whence);
      goFile = lseek(input_fd, bytes, SEEK_SET);
      if(goFile == -1)
      {
	ret = errno;
	perror("error opening the goFile lseek\n");
	goto close_file;
      }

      //read from the first input file
      //ssize_t read(int fd, void *buf, size_t count);
      readFile1 = read(input_fd, buf1, BUF_SIZE);
      if(readFile1 == -1)
      {
	ret = errno;
	perror("error opening the second readFile1\n");
	goto close_file;
      }
      for(k=0;k<readFile1;k++)
      {
	bytes1++;   //bytes1 count
	if(buf1[k]==10)  //newline comes means here break condition
	{
	  break;
	}
      }

      //write the first input file write from first output file
      //ssize_t write(int fd, const void *buf, size_t count);
      writeFile = write(output_fd1, buf1, bytes1);
      if(writeFile == -1)
      {
	ret = errno;
	perror("error opening the first write file\n");
	goto close_file;
      }
      s=s+bytes1;  //here sum of bytes1

      //lseek set output file SEEK_SET
      //off_t lseek(int fd, off_t offset, int whence);
      goFile1 = lseek(output_fd1, s, SEEK_SET);
      if(goFile1 == -1)
      {
	ret = errno;
	perror("error opening the second lseek goFile2\n");
	goto close_file;
      }
      bytes1=0;
      file++;   //increase the input values
      sum++;
    }
  }
   //close a file descriptor
close_file:
  close(input_fd);
  close(output_fd1);
close_exit:
 close(-ret);
}

