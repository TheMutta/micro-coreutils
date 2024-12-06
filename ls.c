#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>

int main(int argc, char **argv) {
	if (argc != 2) return -1;

	printf("Listing of %s\n", argv[1]);

	DIR *dir = opendir(argv[1]);
	struct dirent *entry = readdir(dir);
	while(entry) {
		if (entry->d_name[0] != '.') {
			printf("%s\t", entry->d_name);
		}
		entry = readdir(dir);
	}

	printf("\n");

	closedir(dir);

	return 0;
}
