#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/sysmacros.h>
#include <pwd.h>
#include <grp.h>
#include <fcntl.h>
#include <time.h>

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

const char* permissionCharacters[] = {"---", "--x", "-w-", "-wx", "r--", "r-x", "rw-", "rwx"};

void GetFilePermissions(mode_t mode, char *buf) {
	// User permissions
	strcpy(buf, permissionCharacters[(mode >> 6) & 07]);
	printf("%c", buf[0] == '-' ? 'd' : (S_ISDIR(mode) ? 'd' : '-')); // Add directory indicator

	// Group permissions
	strcat(buf + 1, permissionCharacters[(mode >> 3) & 07]);

	// Others permissions
	strcat(buf + 4, permissionCharacters[mode & 07]);

	// Sticky bit and special modes (e.g., setuid, setgid)
	if (S_ISUID & mode) buf[3] = 's';
	if (S_ISGID & mode) buf[6] = 's';
	if (S_ISVTX & mode) buf[9] = 't';
}

int main(int argc, char **argv) {
	if (argc != 2) return -1;

	struct stat stats;
	stat(argv[1], &stats);

	printf("  File: %s\n", argv[1]);
	printf("  Size: %lu\tBlocks: %lu\tIO Block: %lu\t%s\n",
	       stats.st_size, stats.st_blocks, stats.st_blksize, GetFileType(stats));
	printf("Device: %u,%u\tInode: %lu\tLinks: %lu\n",
	       major(stats.st_dev), minor(stats.st_dev), stats.st_ino, stats.st_nlink);

	char permissionBuf[100] = { 0 };
	GetFilePermissions(stats.st_mode, permissionBuf);
	printf("Access: (%o/%s)\tUid: ( %d/ %s)\tGid: ( %d/ %s)\n",
	       stats.st_mode & 999, permissionBuf,
	       stats.st_uid, getpwuid(stats.st_uid)->pw_name,
	       stats.st_gid, getgrgid(stats.st_gid)->gr_name
	);
	
	char timeBuf[100] = { 0 };
	strftime(timeBuf, sizeof(timeBuf), "%y/%m/%d %T", gmtime(&stats.st_atim.tv_sec));
	printf("Access: %s\n", timeBuf);
	strftime(timeBuf, sizeof(timeBuf), "%y/%m/%d %T", gmtime(&stats.st_mtim.tv_sec));
	printf("Modify: %s\n", timeBuf);
	strftime(timeBuf, sizeof(timeBuf), "%y/%m/%d %T", gmtime(&stats.st_mtim.tv_sec));
	printf("Change: %s\n", timeBuf);
	strftime(timeBuf, sizeof(timeBuf), "%y/%m/%d %T", gmtime(&stats.st_ctim.tv_sec));
	printf(" Birth: %s\n", timeBuf);

	return 0;
}
