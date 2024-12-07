#include <unistd.h>
#include <stdio.h>
#include <pwd.h>

int main(int argc, char **argv) {
	uid_t uid = getuid();
	char *name = getpwuid(uid)->pw_name;

	printf("%s\n", name);
}
