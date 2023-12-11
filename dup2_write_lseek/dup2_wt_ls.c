/***************************************************************************/
/* Author          : Murugan M                                             */
/* Date            : 10/12/2023                     			   */
/* file name       : dup2_write_lseek              		           */
/* Description     : using system call open(),dup2(),read(),lseek(),write()*/
/***************************************************************************/


#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>

#define BUF_SIZE 21
#define BUF_SIZE1 11
int main(int argc, char *argv[])
{
  int input_fd,dup2File;
  off_t goFile1,goFile2;
  ssize_t readBytes1,readBytes2,readBytes3,readBytes4,writeBytes1,writeBytes2;
  char buf[BUF_SIZE] = "wellness and health\n";
  char buf1[BUF_SIZE1] = {'\0'}; //partial initialisation 
  int ret_val = EXIT_SUCCESS; //return value

  //Step1 - open a text file (read and write)
  //int open(const char *pathname, int flags);
  input_fd = open(argv[1], O_RDWR);
  if(input_fd == -1)
  {
    ret_val = errno;
    perror("open : error opening the input_fd");
    goto close_exit;
  }

  //Step2 - call dup2() by passing fd from step 1 as old fd (fd1) and any unused fd as new fd (fd2)
  //int dup2(int oldfd, int newfd);
  dup2File = dup2(input_fd, 4);
  if(dup2File == -1)
  {
    ret_val = errno;
    perror("dup2 : error opening the dup2File");
    goto close_file; 
  }

  //Step3 - write 20 bytes of string to fd1
  //ssize_t write(int fd, const void *buf, size_t count);
  writeBytes1 = write(input_fd, buf, BUF_SIZE-1);
  if(writeBytes1 == -1)
  {
    ret_val = errno;
    perror("write : error opening the writeBytes1");
    goto close_2files; //the first and second file close here
  }

  // Step4 - write 20 bytes of string to fd2
  //ssize_t write(int fd, const void *buf, size_t count);
  writeBytes2 = write(dup2File, "school of linux dpi\n", BUF_SIZE-1);
  if(writeBytes2 == -1)
  {
    ret_val = errno;
    perror("write : error opening the writeBytes2");
    goto close_2files;
  }
  
  //Step5 - use lseek() to move the file position of fd1 to 0
  //off_t lseek(int fd, off_t offset, int whence);
  goFile1 = lseek(input_fd, 0, SEEK_SET);
  if(goFile1 == -1)
  {
    ret_val = errno;
    perror("lseek : error opening the goFile1");
    goto close_2files;
  }

  //Step6 - read and print 10 bytes from fd1
  //ssize_t read(int fd, void *buf, size_t count);
  readBytes1 = read(input_fd, buf1, BUF_SIZE1-1);
  if(readBytes1 == -1)
  {
    ret_val = errno;
    printf("read : error opening the readBytes1");
    goto close_2files;
  }
  printf("readBytes1 10 for input_fd : %s\n",buf1);

  //Step7 - read and print 10 bytes from fd2
  //ssize_t read(int fd, void *buf, size_t count);
  readBytes2 = read(dup2File, buf1, BUF_SIZE1-1);
  if(readBytes2 == -1)
  {
    ret_val = errno;
    perror("read : error opening the readBytes2");
    goto close_2files;
  }
  printf("readBytes2 10 for dup2File : %s\n",buf1);
  
  //Step8 - do step6
  //ssize_t read(int fd, void *buf, size_t count);
  readBytes3 = read(input_fd, buf1, BUF_SIZE1-1);
  if(readBytes3 == -1)
  {
    ret_val = errno;
    perror("read : error opening the readBytes3");
    goto close_2files;
  }
  printf("readBytes3 10 for input_fd : %s\n",buf1);
  
  //Step9 - do step7
  //ssize_t read(int fd, void *buf, size_t count);
  readBytes4 = read(dup2File, buf1, BUF_SIZE1-1);
  if(readBytes4 == -1)
  {
    ret_val = errno;
    perror("read : error opening the readBytes4");
    goto close_2files;
  }
  printf("readBytes4 10 for dup2File : %s\n",buf1);
  //exit(EXIT_SUCCESS);
  ret_val = EXIT_SUCCESS; //sucess the value for 0
 
  /* Step10 - close fd1 and fd2 */
   close_2files: //step3 clean up
     printf("close a two files coming for label\n");
     close(dup2File);
   close_file:  //step2 clean up
     printf("close a one file coming for label\n");
     close(input_fd);
   close_exit:  //step1 clean up
     printf("program exits\n");
     exit(ret_val); //exit 0 come means success
}



/* output

   step1 : murugan@HP:~/linux_api/ass/dup2_write_lseek$ -----gcc dup2_wt_ls.c  -o dup2
           murugan@HP:~/linux_api/ass/dup2_write_lseek$ -----./dup2 sam.txt

           readBytes1 10 for input_fd : wellness a
           readBytes2 10 for dup2File : nd health

   	   readBytes3 10 for input_fd : school of
           readBytes4 10 for dup2File : linux dpi

           close a two files coming for label
           close a one file coming for label
           program exits 

           murugan@HP:~/linux_api/ass/dup2_write_lseek$  ----echo $?
           0 -------->this for 0 means program success            

          =======down this error handling checking=========
 
  step2 : murugan@HP:~/linux_api/ass/dup2_write_lseek$  ----./dup2
          open : error opening the input_fd: Bad address
          program exits

          murugan@HP:~/linux_api/ass/dup2_write_lseek$  ----echo $?
          14 ---------> this for error value                          
         
	  =======file permission change after error handling cheking========

  step3 : murugan@HP:~/linux_api/ass/dup2_write_lseek$ ------chmod 464 sam.txt 
          murugan@HP:~/linux_api/ass/dup2_write_lseek$ ------ls -l
          total 1
          -r--rw-r-- 1 murugan murugan   122 Dec 11 16:58 sam.txt

          murugan@HP:~/linux_api/ass/dup2_write_lseek$ -----./dup2 sam.txt 
          open : error opening the input_fd: Permission denied
          program exits

          murugan@HP:~/linux_api/ass/dup2_write_lseek$ -----echo $?
          13 ------->when your file permission change means this 13 value only come

  step4 : murugan@HP:~/linux_api/ass/dup2_write_lseek$ -----chmod 262 sam.txt 
          murugan@HP:~/linux_api/ass/dup2_write_lseek$ -----ls -l
          total 1
          --w-rw--w- 1 murugan murugan   122 Dec 11 16:58 sam.txt            

          murugan@HP:~/linux_api/ass/dup2_write_lseek$ ------./dup2 sam.txt 
          open : error opening the input_fd: Permission denied
          program exits

          murugan@HP:~/linux_api/ass/dup2_write_lseek$ ------echo $?
          13 ------->when your file permission change means this 13 value only come   */
