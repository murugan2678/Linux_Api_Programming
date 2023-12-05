//Write a program for chown() 

/********************************************************************/
/* Author          : Murugan M                                      */
/* Date            : 22/11/2023                                     */
/* file name       : chown                                          */
/* Description     : using system call for chown(),owner and group  */
/********************************************************************/


#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>

//argc for argument counter, argv for argument vector, using for character * pointer
int main(int argc, char *argv[])
{
  int b,ch;
  uid_t uid; //uid_t data type for integer,user id

  //int atoi(const char *nptr);
  uid = atoi(argv[1]); //atoi for convert a string to an integer
  b = atoi(argv[2]);   //atoi for convert a string to an integer
  int ret_val = EXIT_SUCCESS;

  //change ownership of a file, first pathname giving for txt.file, user id 1000 and group id 1000
  //now i give for  user id = 1000 and root user id = 0, exchange for group id
  //int chown(const char *pathname, uid_t owner, gid_t group); 
  ch = chown("txt.file", uid, b);
  if(ch == -1)
  {
    ret_val = errno;
    perror("chown()");
    exit(-ret_val);
  }
}











/* output
   
   murugan@HP:~/linux_api/ass/chown$ gcc 1.c

   murugan@HP:~/linux_api/ass/chown$ sudo ./a.out 1000 0  ------> user id and group id for 1000, root user id for 0
   murugan@HP:~/linux_api/ass/chown$ ls -l                   |---->now i exchange for group id to root user id 
   total 119228
   -rw-rw-r-- 1 murugan murugan      1210 Dec  5 13:30 1.c
   -rwxrwxr-x 1 murugan murugan     16136 Dec  5 14:07 a.out
   -rw-rw-r-- 1 murugan root           16 Nov 22 13:29 txt.file  ----->now i exchange for group id = 1000 to root user id = 0

   murugan@HP:~/linux_api/ass/chown$ sudo ./a.out 0 1000
   murugan@HP:~/linux_api/ass/chown$ ls -l
   total 119228
   -rw-rw-r-- 1 murugan murugan      1210 Dec  5 13:30 1.c
   -rwxrwxr-x 1 murugan murugan     16136 Dec  5 14:07 a.out
   -rw-rw-r-- 1 root    murugan        16 Nov 22 13:29 txt.file ------>now i exchange for user id = 0 to root user id = 1000

   murugan@HP:~/linux_api/ass/chown$ sudo ./a.out 1000 1000
   murugan@HP:~/linux_api/ass/chown$ ls -l
   total 119228
   -rw-rw-r-- 1 murugan murugan      1210 Dec  5 13:30 1.c
   -rwxrwxr-x 1 murugan murugan     16136 Dec  5 14:07 a.out
   -rw-rw-r-- 1 murugan murugan        16 Nov 22 13:29 txt.file  ------>now i exchange for normal user id = 1000, group id = 1000 */
