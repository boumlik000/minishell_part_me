#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<stdlib.h>

#define BUFFER_S 80
char buffer[BUFFER_S];

int main(int ac, char  *av[])
{
    
    // printf("%ld",size);
    int fd = 0;
    // fd = open("ww",O_RDONLY);
    if (ac > 1)
    {
        fd = open(av[1],O_RDONLY);
        if (fd == -1)
        {
            perror("fd");
            exit(1);
        }
        
    }
    

    ssize_t size ;
    while (size = read(fd,buffer,BUFFER_S))
        write(1,buffer,size);
    
    close(fd);

    return 0;
}
