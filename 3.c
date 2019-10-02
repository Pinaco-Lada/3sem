#include <stdio.h>

int main (int argc, char* argv[], char* envp[]) {
	printf("argc = %d\n", argc);
	int i;
	for (i = 0; i < argc; ++i)
		printf("argv[%d]: '%s'\n", i, argv[i]);
	while (*envp) {
		printf("%s\n", *envp);
		++envp;
	}
	return 0;
}
