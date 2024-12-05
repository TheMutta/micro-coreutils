#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/sysmacros.h>
#include <fcntl.h>

const char *GetFileType(struct stat stats) {
	mode_t mode = stats.st_mode;

	if(S_ISREG(mode)) {
		return "regular file";
	} else if(S_ISDIR(mode)) {
		return "directory";
	} else if(S_ISCHR(mode)) {
		return "character device";
	} else if(S_ISBLK(mode)) {
		return "block device";
	} else if(S_ISFIFO(mode)) {
		return "FIFO";
	} else if(S_ISLNK(mode)) {
		return "symbolic link";
	} else if(S_ISSOCK(mode)) {
		return "socket";
	}

	return NULL;
}

int main(int argc, char **argv) {
	if (argc != 2) return -1;

	struct stat stats;
	stat(argv[1], &stats);

	printf("File: %s\n", argv[1]);
	printf("Size: %lu\tBlocks: %lu\tIO Block: %lu\t%s\n",
	       stats.st_size, stats.st_blocks, stats.st_blksize, GetFileType(stats));
	printf("Device: %u,%u\tInode: %lu\tLinks: %lu\n",
	       major(stats.st_dev), minor(stats.st_dev), stats.st_ino, stats.st_nlink);
	/*
	printf("Access (%.4d/%s)\tUid: ( %d/ %s)\tGid: ( %d/ %s)",
	       stats.st_mode, */

	return 0;
}
