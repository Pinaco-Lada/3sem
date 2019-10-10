#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>  
#include <fcntl.h>

char* NAME[] = {"myfifo.fifo", "myfifo1.fifo"};

void mes(int uid) {
	int m = mkfifo (NAME[1 -uid], 0666);
	if (m == -1) {
		fprintf(stderr, "Error: can't make FIFO\n");
		exit(0);
	}
	int fd_fifo[2]; 
	if ((fd_fifo[1 - uid] = open(NAME[1 - uid], 0666)) == -1) {
		fprintf(stderr, "Error: can't open FIFO\n");
		exit(0);
	}
	while ((fd_fifo[uid] = open(NAME[uid], 0666)) == -1) {
	}
	sleep(1);
	unlink(NAME[1 - uid]);
	char* strr = (char*)malloc(sizeof(char) * 140);
	char* strw = (char*)malloc(sizeof(char) * 140);
	pid_t pid = fork();
	if (pid == -1) {
		fprintf(stderr, "Error: can't fork\n");
		exit(0);
	}
	while(1) {
		if(pid == 0) {
			fgets(strw, 140, stdin);
			int cs = write(fd_fifo[uid], strw, strlen(strw));
		} else {
			int cs = read(fd_fifo[1 - uid], strr, 140);
			int s = 0;
			while (s < 140 && strr[s] != '\n')
				s++;
			strr[s] = '\0';
			printf("\n(=^_^=) : %s\n", strr);
		}
	}
	free(strr);
	free(strw);
}

int main (int argc, char* argv[]) {
	mes (atoi(argv[1]));
	return 0;
}
