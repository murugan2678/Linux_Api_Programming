/* Step1 - call dup2() by passing stdout as old fd and an unused fd as new fd
   Step2 - use write() to write some string into the new fd.
   Step3 - run the program and analyze the result  */


/***********************************************************/
/* Author          : Murugan M                             */
/* Date            : 5/12/2023                             */
/* file name       : dup2_write                            */
/* Description     : using system call for dup2(), write() */
/***********************************************************/


#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>

#define BUF_SIZE 29 //buffer size
int main()
{
  int dup2_File;
  ssize_t writeBytes; //signed integer
  char buf[29] = "Life is a dream - realize it\n"; //using string, character buf size 29
  int ret_val = EXIT_SUCCESS;

  //Step1 - call dup2() by passing stdout as old fd and an unused fd as new fd
  //int dup2(int oldfd, int newfd);
  dup2_File = dup2(STDOUT_FILENO, 4); //stdout means 1
  if(dup2_File == -1)
  {
    ret_val = errno;
    perror("dud2 : error open the dup2File");
    goto close_exit;
  }
  printf("dup2File  : %d\n",dup2_File); //dup2 return value print

  //Step2 - use write() to write some string into the new fd.
  //ssize_t write(int fd, const void *buf, size_t count);
  writeBytes = write(dup2_File, buf, BUF_SIZE);
  if(writeBytes == -1)
  {
    ret_val = errno;
    perror("write : error open the writeFile");
    goto close_file;
  }
  printf("writeBytes  : %ld\n",writeBytes); //how many bytes come print

  //close a file descripator
  close_file:
    close(dup2_File);
  close_exit:
    close(-ret_val);
}


/* output

   dup2File  : 4
   Life is a dream - realize it
   writeBytes  : 29                  */
