#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define CHUNK_SIZE (1024 * 512)

int main(int argc, char **argv) {
	if (argc != 2) return -1;

	int catFd = open(argv[1], O_RDONLY);

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
