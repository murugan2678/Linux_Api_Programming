//write a program for umask()

/************************************************************/
/* Author          : Murugan M                              */
/* Date            : 29/11/2023                             */
/* file name       : umask                                  */
/* Description     : using system call for open(),
                     umask() change the file permission for    
                     user,group,others                      */
/************************************************************/


#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>


//argc for argument counter, argv for argument vector, using for character pointer,array[]
int main(int argc, char *argv[])
{
  int open_fd;
  mode_t mask1,mask2; //mode_t set for file permission

  int ret_val = EXIT_SUCCESS;

  //octal 0666 for default file permission, user give a octal value for 0333 
  //first take user value not gate using,after and gate 
  //mode_t umask(mode_t mask);
  mask1 = umask(0666 & (~0333));

  //default value for umask 0002 this for octal value
  mask2 = umask(0002);
  
  //open the file pathname, flags giving for creat and read only file, modet_t mask2 set file permission
  //int open(const char *pathname, int flags, mode_t mode);
  open_fd = open(argv[1], O_CREAT | O_RDONLY, mask2);
  if(open_fd == -1)
  {
    ret_val = errno;
    perror("open()");
    goto close_exit;
  }
  else
  {
    //open file success
    perror("open()");
  }
  //close a file descriptor
  close_exit:
  close(-ret_val);
}
