#include <sys/utsname.h>
#include <stdio.h>

int main(int argc, char **argv) {

	struct utsname stats;
	uname(&stats);

	printf("%s %s %s %s %s\n", stats.sysname, stats.nodename, stats.release, stats.version, stats.machine);
}
