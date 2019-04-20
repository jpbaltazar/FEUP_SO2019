#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char* argv[], char* envp[]){
    int rc = fork();

    if(rc < 0 || argc < 2){//WHO CARES
        exit(1);
    }
    else if(rc == 0){
        char* arguments[] = {"gcc", argv[1], 0};
        execve("/usr/bin/gcc", arguments, envp);
    }
    else{
        wait();
    }
}