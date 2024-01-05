/* Create the home directory template and copy the default config files into it. 
   Default files are .bashrc and .vimrc in this case */

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>

#define BUF_SIZE 59  //vimrc file size
#define BUF_SIZE1 3772 //basrc file size
int main(int argc, char *argv[])
{
  int mk_file,mk1_file,ch_file,i,input_fd1,output_fd1,input_fd2,output_fd2;

  char buf[BUF_SIZE];
  char buf1[BUF_SIZE1];
  ssize_t readFile1,writeFile1,readFile2,writeFile2;
  mode_t filePerm; 

  filePerm = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH; //filepermission
  int ret_val = EXIT_SUCCESS;
  
  //step1 : first mkdir create directory for Home directory and file permission give for Home directory
  //int mkdir(const char *pathname, mode_t mode);
  mk_file = mkdir(argv[1], 0777);
  if(mk_file == -1)
  {
    ret_val = errno;
    perror("mkdir : error opening the mk_file");
    goto close_exit;
  }
  
  //step2 : change the directory for Home 
  //int chdir(const char *path);
  ch_file = chdir("Home");
  if(ch_file == -1)
  {
    ret_val = errno;
    perror("chdir : error opening the ch_file");
    goto close_exit;
  }
  
  //step3 : Home directory inside directory create for Desktop,Documents,Download,Music,Pictures,Templates,Videos 
  for(i=2; i<argc; i++) //argc for arguments counts
  {
    //int mkdir(const char *pathname, mode_t mode);
    mk1_file = mkdir(argv[i], 0777); 
    if(mk1_file == -1)
    {
      ret_val = errno;
      perror("mkdir : error opening the mk1_file");
      goto close_exit;
    }
  }

  //step4 :  copy the default config files for .vimrc file
  //open the vimrc pathname, that file as read only
  //int open(const char *pathname, int flags);
  input_fd1 = open("/home/murugan/.vimrc", O_RDONLY);
  if(input_fd1 == -1)
  {
    ret_val = errno;
    perror("open : error opening the input_fd");
    goto close_exit;
  }

  //step5 : output_fd1 file inside duplicate pathname given for .vimrc file
  //that files as flags for creat and read, write giving after filepermission given
  //int open(const char *pathname, int flags, mode_t mode);
  output_fd1 = open(".vimrc", O_CREAT | O_RDWR, filePerm);
  if(output_fd1 == -1)
  {
    ret_val = errno;
    perror("opne : error opening the output_fd");
    goto close_file;
  }
 
  //step6 : read the file for input_fd1, buf size for minus 1, reduce the one byte
  //ssize_t read(int fd, void *buf, size_t count);
  readFile1 = read(input_fd1, buf, BUF_SIZE-1);
  if(readFile1 == -1)
  {
    ret_val = errno;
    perror("read : error opening the readFile");
    goto close_2files;
  }

  //step7 : write the file for output_fd1 after the readFile1
  //ssize_t write(int fd, const void *buf, size_t count);
  writeFile1 = write(output_fd1, buf, readFile1);
  if(writeFile1 == -1)
  {
    ret_val = errno;
    perror("write : error opening the writeFile");
    goto close_2files;
  }
  
  //step8 :  copy the default config files for .bashrc file
  //open the .bashc pathname, that file as read only
  //int open(const char *pathname, int flags);
  input_fd2 = open("/home/murugan/.bashrc", O_RDONLY);
  if(input_fd2 == -1)
  {
    ret_val = errno;
    perror("open : error opening the input_fd2");
    goto close_2files;
  }
  
  //step9 : output_fd2 file inside duplicate pathname given for .bashrc file
  //that files as flags for creat and read, write giving after filepermission given
  //int open(const char *pathname, int flags, mode_t mode);
  output_fd2 = open(".bashrc", O_CREAT | O_RDWR, filePerm);
  if(output_fd2 == -1)
  {
    ret_val = errno;
    perror("open : error opening the output_fd2");
    goto close_3files;
  }
  
  //step10 : read the file for input_fd2, buf size for minus 1, reduce the one byte
  //ssize_t read(int fd, void *buf, size_t count);
  readFile2 = read(input_fd2, buf1, BUF_SIZE1-1);
  if(readFile2 == -1)
  {
    ret_val = errno;
    perror("read : error opening the readFile2");
    goto close_4files;
  }

  //step11 : write the file for output_fd1 after the readFile1
  //ssize_t write(int fd, const void *buf, size_t count);
  writeFile2 = write(output_fd2, buf1, readFile2);
  if(writeFile2 == -1)
  {
    ret_val = errno;
    perror("write : error opening the writeFile2");
    goto close_4files;
  }
  exit(EXIT_SUCCESS);
  //step12 : close the file descriptor
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
