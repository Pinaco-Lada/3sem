#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define BUF_SIZE 256
#define FILE_NAME "input.txt"
#define DELIM " \n"

int isdelim(char c, char* delim);
int words_count(char* str, char* delim);
void split(char* src, char*** dest, char* delim);
void exec_str(char* str);

int main() {
	FILE* file = fopen(FILE_NAME, "r");
	if (file == NULL) {
		printf("Error: Can't open file '%s'\n", FILE_NAME);
		exit(1);
	}	

	char buf[BUF_SIZE];
	int commands_count = atoi(fgets(buf, BUF_SIZE, file));

	int i;
	for (i = 0; i < commands_count; ++i) {
		fgets(buf, BUF_SIZE, file);
		
		pid_t pid = fork();
		
		if (pid == -1) {
			printf("Error: Can't fork\n");
			exit(2);
		} else if (pid == 0) {
			exec_str(buf);
		}
	}
return 0;
}

int isdelim(char c, char* delim) {
	while (*delim) {
		if (*delim == c)
			return 1;
		++delim;
	}
	return 0;
}

int words_count(char* str, char* delim) {	
	int count = 1;
	int is_last_delim = 0;
	while (*str) {
		if (isdelim(*str, delim)) {
			if (!is_last_delim)
				count++;
			is_last_delim = 1;
		} else {
			is_last_delim = 0;
		}
		++str;
	}

	return count;
}

void split(char* src, char*** dest, char* delim) {
	int wc = words_count(src, delim);
	*dest = (char**)malloc(sizeof(char*) * (wc + 1));
	char** word = *dest;	

	char* token = strtok(src, delim);	
	while (token) {
		*word = (char*)malloc(sizeof(char) * (strlen(token) + 1));
		strcpy(*word, token);
		++word;
		token = strtok(NULL, delim);
	}
	*word = NULL;
}

void exec_str(char* str) {
	char** argv = NULL;
	
	split(str, &argv, DELIM);
	sleep(atoi(argv[0]));
	execvp(argv[1], argv + 1);
	
	printf("Error: Can't exec %s", argv[1]);
	exit(3);	
}
