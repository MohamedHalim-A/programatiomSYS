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
	status=mkfifo(tube1, 0666);

	if(status == -1){
		perror("mkfifo");
		exit(0);
	}
	fd=open(tube1, O_WRONLY);
	if(fd == -1){
		perror("open");
		exit(0);
	}
	write(fd, argv[1], strlen(argv[1])*sizeof(char));
	close(fd);
}