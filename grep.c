#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define CHUNK_SIZE (1024 * 512)

int main(int argc, char **argv) {
	if (argc != 3) return -1;

	char *findString = argv[1];
	FILE *grepFile = fopen(argv[2], "r");
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;

	while((nread = getline(&line, &len, grepFile)) != -1) {
		char *ptr = strstr(line, findString);
		if (ptr != NULL) {
			fwrite(line, nread, 1, stdout);
		}
	}

	free(line);

	return 0;
}
