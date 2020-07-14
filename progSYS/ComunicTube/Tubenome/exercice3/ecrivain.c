#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define NMAX 80

int main(){
	int fd;
	char *myfifo1 = "tmp/myfifo1";
	char *myfifo2 = "tmp/myfifo2";

	mkfifo(myfifo1, 0666);

	char arr1[NMAX], arr2[NMAX];

	while(1){
		fd = open(myfifo1, O_WRONLY);

		fgets(arr2, NMAX, stdin);

		write(fd, arr2, strlen(arr2)+1);
		close(fd);

		fd = open(myfifo2, O_RDONLY);
		read(fd, arr1, sizeof(arr1));

		printf("Lecture : %s\n", arr1);
		close(fd);
	}
	return 0;
}