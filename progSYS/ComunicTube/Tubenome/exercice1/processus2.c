#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

#define N 1000

int main(int argc, char* argv[]){
	int fd, status;
	char buffer[N];

	char* tube1 = "/tmp/tube1";

	fd=open(tube1, O_RDONLY);
	if(fd == -1){
		perror("open");
		exit(0);
	}
	read(fd, buffer, N);
	printf("%s\n",buffer);
	close(fd);
}