//write a program for chmod()

/***************************************************/
/* Author          : Murugan M                     */
/* Date            : 25/11/2023                    */
/* file name       : chmod                         */
/* Description     : using system call for chmod()
                     change the permission for    
                     user,group,others             */
/***************************************************/

#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>

//argc for argument counter, argv for argument vector, using for character pointer,array[]
int main(int argc, char *argv[])
{
  int chmd,x,y,sum=0,i=0,oct,val=0;

  //int atoi(const char *nptr);
  x = atoi(argv[1]); //convert a string to an integer
  int ret_val = EXIT_SUCCESS;

  //array store for octal number 0 to 7 
  int arr[8]={00,01,02,03,04,05,06,07};

  while(x>0) //x = 777 value for decimal 
  {
    y=x%10; //x values separate the 7
    x=x/10;
    if(y>=0&&y<=7) //octal for 0 to 7 limit
    {
      //array elements 7<<0 shifting, for first time 0th poistion shifting value come for 7
      //array elements 7<<3 shifting, for second time 3rd poistion shifting value come for 70
      //array elements 7<<6 shifting, for third time 6th poistion shitfting value come for 700
      //ocatal values come
      oct = arr[y]<<i;
      printf("%o\n",oct); //%o this format specifier for octal
    }
    i=i+3;//octal for three digit only, add for 3
    sum = sum+oct; //octal vallues add for 7+70+700,total value come for 777
  }
  printf("octal values = %o\n",sum); //%o this format specifier for octal
  
  //chmod - change permissions of a file, file permissions for user, group and others,
  //user for three permission r for read, w for write, x for others
  //group for three permission r for read, w for write, x for others
  //others for three permission r for read, w for write, x for others
  //all change permission value for octal value only sum = 777

  //int chmod(const char *pathname, mode_t mode);
  chmd =chmod(argv[2], sum);
  if(chmd == -1)
  {
    ret_val = errno;
    perror("chmod()");
    exit(-ret_val);
  }
}

/* output

   murugan@HP:~/linux_api/ass/chmod/ch$ ls -l

   -rw-rw-r-- 1 murugan murugan 2118 Nov 26 10:09 1.c
   -rw-rw-r-- 1 murugan murugan   43 Nov 26 10:10 txtfile  //this file permission for normal
  
   murugan@HP:~/linux_api/ass/chmod/ch$ gcc 1.c -o mod
   murugan@HP:~/linux_api/ass/chmod/ch$ ./mod 642 txtfile 
   2
   40
   600
   octal values = 642

   murugan@HP:~/linux_api/ass/chmod/ch$ ls -l

   -rw-rw-r-- 1 murugan murugan  2129 Nov 26 10:13 1.c
   -rwxrwxr-x 1 murugan murugan 16232 Nov 26 10:13 mod

   -rw-r---w- 1 murugan murugan    43 Nov 26 10:10 txtfile  //this file permission for exchange 642 permission  */
