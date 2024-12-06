#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>
#include <fcntl.h>
#include <sys/stat.h>

int main(int argc, char **argv) {
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

	const char *file = argv[optind];
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

		printf("%lu%s\t%s", size, unit, file);
	} else {
		printf("%lu\t%s", stats.st_size, file);
	}

	close(fd);

}
