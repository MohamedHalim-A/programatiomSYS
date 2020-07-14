#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <ctype.h>
#include <fcntl.h>

#define NMAX 80

int main(){
	int fd1;
	char *myfifo1 = "tmp/myfifo1";
	char *myfifo2 = "tmp/myfifo2";

	mkfifo(myfifo2, 0666);

	char str1[NMAX], str2[NMAX];

	while(1){
		//en premier on ouvre en mode lecture
		fd1 = open(myfifo1, O_RDONLY);
		read(fd1, str1, NMAX);

		printf("Ecrivain : %s \n", str1);
		close(fd1);

		//et puis on ouvre en mode ecriture
		fd1 = open(myfifo2, O_WRONLY);

		/* La majuscule de l'inverse de la chaine*/
		/*****************************************/
		
		int l;
		int i = 0;
		for(l=strlen(str1)-1; l>=0; l--){
			str2[i++] = toupper(str1[l]);
		}
		str2[i]='\0';
		/************************************/

		write(fd1, str2, strlen(str2)+1);
		close(fd1);	
	}
	return 0;
}