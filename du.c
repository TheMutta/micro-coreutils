#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <fcntl.h>
#include <sys/stat.h>

int main(int argc, char **argv) {
	if (argc < 2) {
		fprintf(stderr, "Usage: %s [-h] <file> ...\n", argv[0]);
		return EXIT_FAILURE;
	}

	bool humanReadable = false;
	int opt;
	while ((opt = getopt(argc, argv, "h")) != -1) {
		switch (opt) {
			case 'h':
				humanReadable = true;
				break;
			default:
				printf("Invalid option: %c\n", optopt);
		}
   	}

	for (int i = optind; i < argc; ++i) {
		const char *file = argv[i];
		int fd = open(file, O_RDONLY);

		struct stat stats;
		fstat(fd, &stats);

		if (humanReadable) {
			size_t size = stats.st_size;
			char *unit;
			if (size >= 1024) {
				if (size >= 1024 * 1024) {
					if (size >= 1024 * 1024 * 1024) {
						unit = "GB";
						size /= 1024 * 1024 * 1024;
					} else {
						unit = "MB";
						size /= 1024 * 1024;
					}
				} else {
					unit = "KB";
					size /= 1024;
				}
			} else {
				unit = "B";
			}

			printf("%lu%s\t%s\n", size, unit, file);
		} else {
			printf("%lu\t%s\n", stats.st_size, file);
		}
	
		close(fd);
	}
}
