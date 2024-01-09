/* write a program to delete the files and directories created in assignment 15 */

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>

#define BUF_SIZE 59    //.vimrc file size
#define BUF_SIZE1 3847 //.bashrc file size
int main(int argc, char *argv[])
{
  int input_fd1,input_fd2,output_fd1,output_fd2,mk1_file,mk2_file,ch1_file,ch2_file,rm1_file,rm2_file,link1_file,link2_file,i;

  ssize_t readFile1,readFile2,writeFile1,writeFile2;
  char buf[BUF_SIZE]; //character and buffer size for vimrc 
  char buf1[BUF_SIZE1]; //character and buffer size for bashrc
  mode_t filePerm;  //mode_t set for file permission

  filePerm = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH; //file permission for user, group and others
  int ret_val = EXIT_SUCCESS;

  //step1 : first create the Home directory and give a file permission for user,group and others
  //int mkdir(const char *pathname, mode_t mode);
  mk1_file = mkdir(argv[1], 0777);
  if(mk1_file == -1)
  {
    ret_val = errno;
    perror("mkdir : error opening the mk1_file");
    goto close_exit;
  }
  
  //step2 : after the change a home directory 
  //int chdir(const char *path);
  ch1_file = chdir("Home");
  if(ch1_file == -1)
  {
    ret_val = errno;
    perror("chdir : error opening the ch1_file");
    goto close_exit;
  }
  
  //step3 : create directory form home directory templates for Desktop,Documents,Downloads,Music,Pictures,Videos,Templetes
  for(i=2; i<argc; i++)
  {
    //int mkdir(const char *pathname, mode_t mode);
    mk2_file = mkdir(argv[i], 0777);
    if(mk2_file == -1)
    {
      ret_val = errno;
      perror("mkdir : error opening the mk1_file");
      goto close_exit;
    }
  }
  
  //step4 : .vimrc pathname give open the .vimrc file and that file as read only
  //int open(const char *pathname, int flags);
  input_fd1 = open("/home/murugan/.vimrc", O_RDONLY);
  if(input_fd1 == -1)
  {
    ret_val = errno;
    perror("open : error opening the input_fd1");
    goto close_exit;
  }

  //step5 : after the create the file read and write only, filepermission give for user,group,others
  //int open(const char *pathname, int flags, mode_t mode);
  output_fd1 = open(".vimrc",O_CREAT | O_RDWR, filePerm);
  if(output_fd1 == -1)
  {
    ret_val = errno;
    perror("open : error opening the output_fd1");
    goto close_file;
  }

  //step6 : read the input_fd1 file and the buf set,buffer size give minus one byte
  //ssize_t read(int fd, void *buf, size_t count);
  readFile1 = read(input_fd1, buf, BUF_SIZE-1);
  if(readFile1 == -1)
  {
    ret_val = errno;
    perror("read : error opening the readFile1");
    goto close_file;
  }

  //step7 : write the output_fd1 file and buf set, read the readFile1 file
  //ssize_t write(int fd, const void *buf, size_t count);
  writeFile1 = write(output_fd1, buf, readFile1);
  if(writeFile1 == -1)
  {
    ret_val = errno;
    perror("write : error opening the writeFile1");
    goto close_2files;
  }

  //step8 : .bashrc the pathname give open the .bashrc file and that file as read only
  //int open(const char *pathname, int flags);
  input_fd2 = open("/home/murugan/.bashrc", O_RDONLY);
  if(input_fd2 == -1)
  {
    ret_val = errno;
    perror("open : error opening the input_fd2");
    goto close_2files;
  }

  //step9 : after the create the file read and write only, filepermission give for user,group,others
  //int open(const char *pathname, int flags, mode_t mode);
  output_fd2 = open(".bashrc",O_CREAT | O_RDWR, filePerm);
  if(output_fd2 == -1)
  {
    ret_val = errno;
    perror("open : error opening the output_fd2");
    goto close_3files;
  }

  //step10 : read the input_fd2 file and the buf1 set,buffer size1 give minus one byte
  //ssize_t read(int fd, void *buf, size_t count);
  readFile2 = read(input_fd2, buf1, BUF_SIZE1-1);
  if(readFile2 == -1)
  {
    ret_val = errno;
    perror("read : error opening the readFile2");
    goto close_4files;
  }

  //step10 : write the output_fd2 file and buf1 set, read the readFile2 file
  //ssize_t write(int fd, const void *buf, size_t count);
  writeFile2 = write(output_fd2, buf1, readFile2);
  if(writeFile2 == -1)
  {
    ret_val = errno;
    perror("write : error opening the writeFile2");
    goto close_4files;
  }

  //step11 : deletes a name from the filesystem, .vimrc delete the file
  //int unlink(const char *pathname);
  link1_file = unlink(".vimrc");
  if(link1_file == -1)
  {
    ret_val = errno;
    perror("unlink : error opening the link1_file");
    goto close_exit;
  }

  //step12 : deletes a name from the filesystem, .bashrc delete the file
  //int unlink(const char *pathname);
  link2_file = unlink(".bashrc");
  if(link2_file == -1)
  {
    ret_val = errno;
    perror("unlink : error opening the link2_file");
    goto close_exit;
  }

  for(i=2; i<argc; i++)
  {   
  //step13 : home directory inside the directory was delete,directory name for Desktop,Documents,Downloads,Music,Pictures,Videos,Templetes
    //int rmdir(const char *pathname);
    rm1_file = rmdir(argv[i]);
    if(rm1_file == -1)
    {
      ret_val = errno;
      perror("rmdir : error opening the rm1_file");
      goto close_exit;
    }
  }
  
  //step14 : home directory change the directory outside came  
  //int chdir(const char *path);
  ch2_file = chdir("..");
  if(ch2_file == -1)
  {
    ret_val = errno;
    perror("chdir : error opening the ch2_file");
    goto close_exit;
  }
  
  //step15 : rmdir reove the home directory
  //int rmdir(const char *pathname);
  rm2_file = rmdir("Home");
  if(rm2_file == -1)
  {
    ret_val = errno;
    perror("rmdir : error opening the rm2_file");
    goto close_exit;
  }
  exit(EXIT_SUCCESS);

  //close file descriptor for fd1,fd2,
  close_4files:
    close(output_fd2);
  close_3files:
    close(input_fd2);
  close_2files:
    close(output_fd1);
  close_file:
    close(input_fd1);
  close_exit:
    exit(ret_val);
}
