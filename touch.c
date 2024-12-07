#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <utime.h>

int main(int argc, char **argv) {
	if (argc != 2) return -1;

	int destFd = open(argv[1], O_RDWR | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);

	close(destFd);

	time_t _time = time(NULL);

	utime(argv[1], &(const struct utimbuf){.actime = _time, .modtime = _time});

	return 0;
}
