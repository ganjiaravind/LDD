#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define DEV_NAME	"/dev/chardev-0"
int main()
{
	int fd;
	fd = open(DEV_NAME, O_RDWR);
	if (fd < 0) {
		printf("failed to open file %s\n", DEV_NAME);
		return fd;
	}
	printf("successfully open device file %s\n", DEV_NAME);
	write(fd, "Hello Dev", sizeof("Hello Dev"));
	close(fd);

	return 0;
}
