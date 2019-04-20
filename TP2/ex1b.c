#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

void clearbuf(char *buf, int size){
    for(int i = 0; i < size; i++) buf[i] = '\0';
}

int main(int argc, char* argv[]){
    int f1 = open(argv[1], O_CREAT|O_RDONLY);
    int f2 = open(argv[2], O_CREAT|O_WRONLY|O_EXCL);

    char buf[64] = {0};

    while(read(f1, buf, 63) != 0){
        write(f2, buf, 63);
        clearbuf(buf, 64);
    }
    //write(STDOUT_FILENO, errno, 1);

    close(f1);
    close(f2);
}
