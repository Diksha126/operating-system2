#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<errno.h>//reads the no of the last error

int main(int argc, char *arg[])
{
int fd[2]; // file descripters for the files
int filebytelen;
char buffer[100];
char childbuffer[100];

char *src=arg[1];
char *dest=arg[2];

if(pipe(fd)<0)
{
printf("error while creating pipe!!!");
exit(1);
}

switch(fork())
{
case -1:
printf("error forking child process \n");
exit(1);
case 0:
close(fd[1]);
ssize_t child_bytes= read(fd[0],childbuffer,sizeof(childbuffer));// reads from the source 
close(fd[0]);

int target=open("dest",O_CREAT|O_WRONLY); 
write(target,childbuffer,child_bytes); // write on the destination.

default:
close(fd[0]);
int fileindes=open(src,O_RDONLY);
ssize_t num_bytes=read(fileindes,buffer,sizeof(buffer));
write(fd[1],buffer,num_bytes);
close(fd[1]);
}
return 0;
}
