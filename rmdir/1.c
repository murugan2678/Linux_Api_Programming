//Write a program for rmdir

/***************************************************/
/* Author          : Murugan M                     */
/* Date            : 18/11/2023                    */
/* file name       : rmdir                         */
/* Description     : using system call for rmdir() */
/***************************************************/


#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>

//argc for argument counter, argv for argument vector, using for character pointer
int main(int argc, char *argv[])
{
  int rm_d;
  int ret_val = EXIT_SUCCESS;
  //rmdir delete a directory
  //int rmdir(const char *pathname);
  rm_d = rmdir(argv[1]);
  if(rm_d == -1)
  {
    ret_val = errno;
    perror("rmdir()");
    exit(-ret_val);
  }
}
