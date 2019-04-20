#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char* argv[], char* envp[]){
    if(argc < 2){
        write(STDERR_FILENO, "\nwrite name of file in arg\n", sizeof("\nwrite name of file in arg\n"));
        exit(1);
    }

    int fd = open("envVars.txt", O_CREAT|O_WRONLY);
    for(int i = 0; envp[i] ; i++)
    {
        write(fd, envp[i], strlen(envp[i]));
        write(fd, "\n", 1);
    }
}