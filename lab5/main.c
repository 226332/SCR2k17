#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
int openFile(char* filename)
{   
    int file;
    if((file=open(filename, O_RDONLY ))<0)
    {
		perror(filename);
        exit(1);
    }
    else return file;
}

void readFile(int writeDescriptor, char* fileName)
{
    int fileDescriptor=openFile(fileName);
    char img[100];
    int i;
    while ((i=read(fileDescriptor, img, sizeof(img)))>0)
	{
		write(writeDescriptor, img, i);
	}
    write(writeDescriptor, "/n", 1);
	close(fileDescriptor);
}

int openFork()
{   
    int pid;
    if((pid=fork())==-1)
    {
        printf("Failed to fork!\n");
        exit(1);
    }
    else return pid;
}

int main (int argc, char **argv)
{
	int fd[2];
    
#ifdef FIFO
    char* fifo="fifko";
    int i;
    if(mkfifo(fifo,0666)<0)
    {
        printf("Failed to mkfifo!\n");
        exit(1);
    }
    for (i=1; i<argc; i++)
    {
        fd[0]=open(fifo,O_WRONLY);
        readFile(fd[0], argv[i]);
        close(fd[0]);
    }
    unlink(fifo);
#endif

#ifdef PIPE
    int pid;
    
	if(pipe(fd)==-1)
    {
        printf("Failed to pipe!\n");
		exit(1);
    }

	pid=openFork();
		
	if(!pid)
	{
		close(0);
		dup(fd[0]);
        close(fd[0]);
        close(fd[1]);
        execlp("display","display", NULL);
	}
    else 
	{   
        
        readFile(fd[1], argv[1]);
	}
#endif
	return 0;
}
