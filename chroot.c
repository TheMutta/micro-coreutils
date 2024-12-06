#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv) {
	if (argc != 2) return -1;

	char *chrootPath = argv[1];

	if(chroot(chrootPath) != 0) {
		perror("chroot");
		return EXIT_FAILURE;
	}

	chdir("/");

	char *args[2] = { "/bin/sh", 0 };
	execv(args[0], args);

	return 0;
}
