#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
	pid_t pid = fork();
	if(pid == -1) {
		printf("Error: Can't fork\n");
		exit(1);
	} else if (pid == 0) {
		execlp("./hello_world", "hello_world", NULL);
		printf("Error: Can't exec\n");
		exit(2);
	}
	return 0;
}
