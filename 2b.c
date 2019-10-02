#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

void forkn (int n) {
	if (n == 0)
		return;
	if (fork() == 0) {
		printf("Process %d was created by process %d\n", getpid(), getppid());
		forkn(n - 1);
	}
	pid_t pid = wait(NULL);
	if (pid != -1)
		printf("Process %d was ended\n", pid);
	exit(n);
}

int main() {
	int i;
	int N;
	scanf("%d", &N);
	printf("Main process %d\n", getpid());
	forkn(N);
	return 0;
}

