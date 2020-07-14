#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>


#define NMAX 100

int main(){
	int fd;
	char *fifotube1 = "/tmp/fifotube1";
	char *fifotube2 = "/tmp/fifotube2";

	mkfifo(fifotube1, 0666);

	char arr1[NMAX], arr2[NMAX];
	while(1){
		fd = open(fifotube1, O_WRONLY);
		fgets(arr2, NMAX, stdin);

		write(fd, arr2, strlen(arr2)+1);
		close(fd);

		fd = open(fifotube2, O_RDONLY);
		read(fd, arr1, sizeof(arr1));

		printf("processus2 : %s\n",arr1);
		close(fd);
	}
	return 0;
}