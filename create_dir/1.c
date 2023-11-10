/* write a program for new `directory create */

//header file
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
  int new_dir,num;
  mode_t filePerm; //mode_t set

  //directory filepermission set
  filePerm = S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IWGRP | S_IXGRP | S_IROTH | S_IXOTH;

  //new directory create,new directory giving a pathname and fileperm 
  //int mkdir(const char *pathname, mode_t mode);
  new_dir = mkdir(argv[1],filePerm);
  if(new_dir == -1)
  {
    perror("error the opening a directory permission denied");
  }
}
