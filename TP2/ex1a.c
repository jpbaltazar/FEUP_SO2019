#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

void clearbuf(char *buf, int size){
    for(int i = 0; i < size; i++) buf[i] = 0;
}

int main(int argc, char* argv[]){
    int f = open(argv[1], O_CREAT|O_RDWR);
    char buf[64] = {0};

    while(read(f, buf, 64) != 0){
        write(STDOUT_FILENO, buf, 64);
        clearbuf(buf, 64);
    }
    write(STDOUT_FILENO, "\n", 1);
}
