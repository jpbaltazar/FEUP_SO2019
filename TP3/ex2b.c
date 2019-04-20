#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char* argv[], char* envp[]){
    int rc = fork();
    if(rc < 0){
        write(STDERR_FILENO, "\nfailed to fork\n", sizeof("\nfailed to fork\n"));
        exit(1);
    }
    else if(rc == 0){ //CHILD
        int fd = open("envVarsChild.txt", O_CREAT|O_WRONLY);
        for(int i = 0; envp[i] ; i++)
        {
            write(fd, envp[i], strlen(envp[i]));
            write(fd, "\n", 1);
        }
        printf("child PID: %d rc = %d\n", getpid(), rc);
    }

    else{
        int fd = open("envVarsParent.txt", O_CREAT|O_WRONLY);
        for(int i = 0; envp[i] ; i++)
        {
            write(fd, envp[i], strlen(envp[i]));
            write(fd, "\n", 1);
        }
        printf("parent PID: %d rc = %d\n", getpid(), rc);

    }
    wait();
    printf("end of PID: %d\n", getpid());

}