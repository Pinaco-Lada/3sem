#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main() {
	int i;
	int N;
	scanf("%d", &N);
	pid_t pid = getpid();
	pid_t p = pid;
	printf("%d\n", getpid());
	for (i = 0 ; i < N; ++i) {
		if (fork() == 0) {
			sleep(i + 1);
			printf("%d %d %d\n" , i, getpid(), getppid());
			exit(i + 1); 
		}
	}
	int retvalue;
	while((pid = wait(&retvalue)) != -1) {
		printf("Waited %d %d\n", pid, retvalue >> 8);
	}
return 0;
}

