//Write a program to create 10 directors, one directory has to be created per second, then delete one by one (one per second). 

/*************************************************************************************************/
/* Author          : Murugan M                                                                   */
/* Date            : 16/11/2023                                                                  */
/* file name       : directory                                                                   */
/* Description     : using 2 system call mkdir() create directory and rmdir() delete a directory */
/*************************************************************************************************/

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>


int main(int argc, char *argv[]) //argc for argument counter, argv for argument vector, using for character pointer
{
  int new_dir,del_dir,i,j,b=1;

  mode_t filePerm; //mode_t set a mode
  int ret_val = EXIT_SUCCESS;
  //file permission set a user for read and write, group for read and write, others for read
  filePerm = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH;

  for(i=1; i<argc; i++) //this loop for create a directory
  {
    //create a new directory, how many directory u want, giving for argument vector
    //directory name example for 1,2,file,i give the permission for all directory 
    //int mkdir(const char *pathname, mode_t mode);
    new_dir = mkdir(argv[i], filePerm);
    if(new_dir == -1)
    {
      perror("mkdir : error opening a new_dir");
    }
    else
    {
      printf("directory name : %s\n",argv[i]); //directory name print
      perror("directory created"); //directory Sucessfully create
      sleep(1); //sleep for 1 second set
    }
  }
  for(j=1; j<argc; j++) //this loop for delete a directory
  {
    //remove delete a directory, befor create the directory, the all directory now remove
    //int rmdir(const char *pathname);
    del_dir = rmdir(argv[j]);
    if(del_dir == -1)
    {
      ret_val = errno;
      perror("rmdir : error opening a del_dir");
      goto close_exit;
    }
    else
    {
      printf("directory name : %s\n",argv[j]); //directory name print
      perror("directory removed"); //directory Sucessfully delete a directory
      sleep(1); //sleep for 1 second set 
    }
  }
  exit(EXIT_SUCCESS);
close_exit:
  exit(ret_val);
}
