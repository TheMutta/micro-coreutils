#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define CHUNK_SIZE (1024 * 512)

int main(int argc, char **argv) {
	if (argc < 3) return -1;

	int opt;
	while ((opt = getopt(argc, argv, "rf")) != -1) {
		switch (opt) {
			case 'r':
				printf("Recursive.\n");
				break;
			case 'f':
				printf("Forced.\n");
				break;
			default:
				printf("Invalid option: %c\n", optopt);
		}
   	}

	const char *origin = argv[optind];
	const char *destination = argv[optind + 1];
	printf("Copiying %s to %s\n", origin, destination);

	int copyFd = open(origin, O_RDONLY);
	int destFd = open(destination, O_WRONLY| O_TRUNC | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);

	struct stat stats;
	fstat(copyFd, &stats);

	size_t copySize = stats.st_size;
	ftruncate(destFd, copySize);
	fchmod(destFd, stats.st_mode);

	char chunk[CHUNK_SIZE];
	for (size_t off = 0; off < copySize; off += CHUNK_SIZE) {
		ssize_t readBytes = read(copyFd, chunk, CHUNK_SIZE);
		ssize_t writtenBytes = write(destFd, chunk, readBytes); 
		printf("Percent: %.2f%%\r", (float)off / copySize * 100);
	}
	
	printf("\nCopy complete\n");

	close(destFd);
	close(copyFd);

	return 0;
}
