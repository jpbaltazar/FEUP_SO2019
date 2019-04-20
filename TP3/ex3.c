#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char* argv[], char* envp[]){
    int rc = fork();
    int exgc = 0;
    int exc = 0;

    if(rc < 0){
        write(STDERR_FILENO, "Oh you fucked up", sizeof("Oh you fucked up"));
        exit(1);
    }

    else if(rc == 0){//CHILD
        printf("hello im child %d, my parent is %d\n", getpid(), getppid());
        int rc2 = fork();
        if(rc2 < 0){
            write(STDERR_FILENO, "Oh you fucked up", sizeof("Oh you fucked up"));
            exit(1);
        }
        else if(rc2 == 0){ //GRANDCHILD
            printf("hello I am grandchild %d, my parent is %d\n", getpid(), getppid());
            exit(3);
        }
        else{ //CHILD
            wait(&exgc);
            printf("PID %d grandchild ended with exit state %d\n", getpid(), WEXITSTATUS(exgc));
            exit(2);
        }
    }
    
    else{//PARENT
        printf("hello im parent %d, my parent is %d\n", getpid(), getppid());
    }
    wait(&exc); //STILL WRONG
    printf("pid %d, child ended with exit state %d\n",getpid(), WEXITSTATUS(exgc));
    return 0;
}