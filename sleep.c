#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv) {
	if (argc != 2) return -1;

	usleep(atoi(argv[1]) * 1000000);

	return 0;
}
