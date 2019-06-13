#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main() {
	// Get the paths.
	char* home = getenv("HOME");
	char* pwdpath = malloc(strlen(home) + 12);
	strcpy(pwdpath, home);
	strcat(pwdpath, "/.config/._");

	char* pwd2path = malloc(strlen(pwdpath) + 2);
	strcpy(pwd2path, pwdpath);
	strcat(pwd2path, "2");

	size_t maxsize = 512;

	// Open '._' and read the first password.
	FILE* pwdfd = fopen(pwdpath, "r+");
	char* candidate = malloc(512);
	getline(&candidate, &maxsize, pwdfd);
	printf("%s", candidate);	// Print it.

	// Fork and manage the files.
	pid_t pid = fork();
	if(pid) {
		fclose(pwdfd);
		return 0;
	}

	// Remove the first line from '._'.
	FILE* pwd2fd = fopen(pwd2path, "w");
	char* tmpline = malloc(512);
	size_t tmpline_sz = 0;
	while((tmpline_sz = getline(&tmpline, &maxsize, pwdfd)) != -1) {
		fwrite(tmpline, 1, strlen(tmpline), pwd2fd);
	}
	fclose(pwd2fd);
	remove(pwdpath);
	rename(pwd2path, pwdpath);

	return 0;
}
