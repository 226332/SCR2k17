#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int openFile(char *fileName)
{
    int file;
    if ((file = open(fileName, O_RDONLY)) < 0)
    {
        perror(fileName);
        exit(1);
    }
    else
        return file;
}

void mapFile(int writeDesc, char *fileName)
{
    struct stat fileStat;
    void *map;
    if (stat(fileName, &fileStat) < 0)
    {
        perror(fileName);
        exit(1);
    }

    ftruncate(writeDesc, fileStat.st_size);
    map = mmap(NULL, fileStat.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, writeDesc, 0);
    if (map == MAP_FAILED)
    {
        perror("Error mmapping the file");
        exit(EXIT_FAILURE);
    }
    int fileDesc = openFile(fileName);
    read(fileDesc, map, fileStat.st_size);
    msync(map, fileStat.st_size, MS_SYNC);
    close(fileDesc);
}

int openFork()
{
    int pid;
    if ((pid = fork()) == -1)
    {
        printf("Failed to fork!\n");
        exit(1);
    }
    else
        return pid;
}

int main(int argc, char **argv)
{
    int status = 0;
    int fd;
    char *memoryFileName = "MemoryComunism";
    int pid;
    int i;
    pid = openFork();

    if (!pid)
    {
#ifndef VALGRIND
        char shmWholeName[50] = "/dev/shm/";
        strcat(shmWholeName, memoryFileName);
        execl("/usr/bin/display", "/usr/bin/display", "-update", "1",
              shmWholeName, (char *)NULL);
#endif
    }
    else
    {
        fd = shm_open(memoryFileName, O_RDWR | O_CREAT, 0666);
        for (i = 1; i < argc; i++)
        {
            mapFile(fd, argv[i]);
            sleep(2); //to see every image
        }
        close(fd);
    }
    shm_unlink(memoryFileName);
    wait(&status);
    return status;
}
