#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

void clearbuf(char *buf, int size){
    for(int i = 0; i < size; i++) buf[i] = '\0';
}

int main(int argc, char* argv[]){
    //int fd = open("joined.txt", O_CREAT|O_WRONLY);
    int prefixLen = strlen(argv[1]);
    char buf[512];
    char *filename = calloc(sizeof(char), (prefixLen+2));
    strcpy(filename, argv[1]);
    filename[prefixLen] = 'a';
    filename[prefixLen+1] = 'a';
    int src = 0;
    for(;;){
        src = open(filename, O_RDONLY);
        if(src == -1) break;
        read(src, buf, 512);
        //write(STDOUT_FILENO, filename, sizeof(filename));
        write(STDOUT_FILENO, buf, 512);
        clearbuf(buf, 512);
        filename[prefixLen + 1]++;
    }
}