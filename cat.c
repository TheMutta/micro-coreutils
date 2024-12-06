#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define CHUNK_SIZE (1024 * 512)

int main(int argc, char **argv) {
	if (argc != 2) {
		fprintf(stderr, "Usage: %s <file>\n", argv[0]);
		return EXIT_FAILURE;
	}

	int catFd = open(argv[1], O_RDONLY);
	if (catFd < 0) {
		perror("open");
		return EXIT_FAILURE;
	}

	struct stat stats;
	fstat(catFd, &stats);

	size_t catSize = stats.st_size;

	char chunk[CHUNK_SIZE];
	for (size_t off = 0; off < catSize; off += CHUNK_SIZE) {
		ssize_t readBytes = read(catFd, chunk, CHUNK_SIZE);
		printf("%s", chunk);
	}
		
	printf("\n");

	close(catFd);

	return 0;
}
