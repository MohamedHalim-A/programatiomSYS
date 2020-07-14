#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#define NMAX 100

int main(){
	int fd1;
	char *fifotube2 = "/tmp/fifotube2";
	char *fifotube1 = "/tmp/fifotube1";

	mkfifo(fifotube2, 0666);

	char str1[NMAX], str2[NMAX];
	while(1){
		fd1 = open(fifotube1, O_RDONLY);
		read(fd1, str1, NMAX);

		printf("processus1 : %s\n",str1);
		close(fd1);

		fd1 = open(fifotube2, O_WRONLY);

		fgets(str2, NMAX, stdin);

		write(fd1, str2, strlen(str2)+1);
		close(fd1);
	}
	return 0;
}