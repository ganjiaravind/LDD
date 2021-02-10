#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define DEV_NAME	"/dev/chardev-0"
int main()
{
	int fd, rc;
	char buf[100] = {'0'};
	fd = open(DEV_NAME, O_RDWR);
	if (fd < 0) {
		printf("failed to open file %s\n", DEV_NAME);
		return fd;
	}
	printf("successfully open device file %s\n", DEV_NAME);
	printf("Please enter data upto 100 byte to send to Device\n");
	fgets(buf, sizeof(buf), stdin);
	rc = write(fd, buf, sizeof(buf));
	if (rc < 0)
		printf("failed to write to %s dev\n", DEV_NAME);
	rc = read(fd, buf, sizeof(buf));
	if (rc < 0)
		printf("failed to read from %s dev\n", DEV_NAME);

	printf("Buffer read from driver is : %s\n", buf);
	close(fd);

	return 0;
}
