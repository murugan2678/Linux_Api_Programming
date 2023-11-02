/* Task 3: write a program to take the line numbers which are multiples of 10. 
   Example - source_file has 100 lines,
   you have to create a file file_10th and save line numbers 10, 20, 30, 40, ... 100  */

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <error.h>
#include <stdlib.h>
#include <stdio.h>

#define BUF_SIZE 102400
int main(int argc, char *argv[]) //argc argument counter, argv argument vector 
{
  int fd,openFlag,createFile,i,k,b,y,m,d,s=0;
  int num,bytes,file,sum=1,bytes1;

  mode_t filePerm;      //mode_t file mode set
  off_t goFile,goFile1; //signed integer file offset
  char buf[BUF_SIZE];   //character buffer store the buffer size
  char buf1[BUF_SIZE];
  ssize_t readFile,readFile1,writeFile; //ssize_t signed integer  
  
  openFlag = O_CREAT | O_RDONLY; //create file that file as readonly
  filePerm = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH; //filepermission giving user,group,others 

  //int open(const char *pathname, int flags, mode_t mode);
  fd = open(argv[1], openFlag, filePerm); //here open a one file,fd file descriptor  
  if(fd == -1)
  {
    perror("error opening the open file\n");
  }
  
  //int creat(const char *pathname, mode_t mode);
  createFile = creat(argv[2], filePerm); //here create file,will create
  if(createFile == -1)
  {
    perror("error opening the create file\n");
  }
  
  //ssize_t read(int fd, void *buf, size_t count);
  readFile = read(fd, buf, BUF_SIZE); //read that open file and buffer size
 
  //int atoi(const char *nptr);
  num=atoi(argv[3]); //convert a string to an integer
  b=0;
  for(i=0;i<readFile;i++)
  {
    bytes++;      //bytes count
    if(buf[i]==10)//newline checking
    {
      b++;        //newline count
    }
    file=(num*sum)-1; //input values here multiplication
    if(b==file)  //here checking newline and input values
    {
      //off_t lseek(int fd, off_t offset, int whence);
      goFile = lseek(fd, bytes, SEEK_SET); //lseek for first open file, bytes giving, SEEK_SET    

      //ssize_t read(int fd, void *buf, size_t count);
      readFile1 = read(fd, buf1, BUF_SIZE); //read that first open file

      for(k=0;k<readFile1;k++)
      {
	bytes1++;       //bytes1 count
	if(buf1[k]==10) //newline comes means here break condition
	{
	  break;
	}
      }

      //ssize_t write(int fd, const void *buf, size_t count);
      writeFile = write(createFile, buf1, bytes1);  //createfile inside write the file
      s=s+bytes1; //here sum of bytes1

      //off_t lseek(int fd, off_t offset, int whence);
      goFile1 = lseek(createFile, s, SEEK_SET);  //createfile inside bytes cursor set
      bytes1=0;
      file++; //increase the input values
      sum++;  
    }
  }
  close(fd); //close file descriptor
  close(createFile); //close createFile
}
