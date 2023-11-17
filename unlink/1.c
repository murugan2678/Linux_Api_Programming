//Write a program for unlink

/********************************************************************************************/
/* Author          : Murugan M                                                              */
/* Date            : 16/11/2023                                                             */
/* file name       : unlink                                                                 */
/* Description     : using system call for unlink(), unlink uses for the file only removed, 
                     unlink not a uses, directory not a deleted                             */
/********************************************************************************************/

#include <unistd.h>
#include <errno.h>
#include <stdio.h>

//argc for argument counter, argv for argument vector, using for character pointer
int main(int argc, char *argv[])
{
  int linkremov;

  //unlink is the at the time one file only delete,unlink for not delete directory 
  //int unlink(const char *pathname);
  linkremov = unlink(argv[1]);
  if(linkremov == -1)
  {
    perror("no such as file");
  }
}
