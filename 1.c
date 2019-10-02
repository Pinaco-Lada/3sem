#include <stdio.h>
#include <unistd.h>

int main() {
	pid_t pid = fork();
	if (pid == -1) {
		printf ("Error: can't fork\n");
	} else if (pid == 0) {
		printf ("I am a child\n");
	} else {
		printf("I am a parent\n");
	}
	return 0;
}
