#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char* argv[], char* envp[]){
    for(int i = 0; i < argc; i++)
    {
        write(STDOUT_FILENO, argv[i], strlen(argv[i]));
        write(STDOUT_FILENO, "\n", 1);
    }

    for(int j = 0; envp[j]; j++)
    {
        write(STDOUT_FILENO, envp[j], strlen(envp[j]));
        write(STDOUT_FILENO, "\n", 1);
    }
}