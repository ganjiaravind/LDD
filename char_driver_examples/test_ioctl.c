#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <errno.h>
#include "char_ioctl.h"

#define DEV_NAME	"/dev/chardev-0"
int main()
{
	int fd;
	int dev_info, rc;
	fd = open(DEV_NAME, O_RDWR);
	if (fd < 0) {
		printf("failed to open file %s\n", DEV_NAME);
		return fd;
	}
	printf("successfully open device file %s\n", DEV_NAME);
	write(fd, "Hello Dev", sizeof("Hello Dev"));
	rc = ioctl(fd, GET_DEV_INFO, &dev_info);
	if (rc < 0) {
		printf("failed to perform ioctl operation\n");
		close(fd);
		return -EINVAL;
	}
	printf("successfully able to read device info %d\n", dev_info);
	dev_info = 200;
	rc = ioctl(fd, SET_DEV_INFO, &dev_info);
	if (rc < 0) {
		printf("failed to perform ioctl operation\n");
		close(fd);
		return -EINVAL;
	}
	rc = ioctl(fd, GET_DEV_INFO, &dev_info);
	if (rc < 0) {
		printf("failed to perform ioctl operation\n");
		close(fd);
		return -EINVAL;
	}
	printf("successfully able to set device info %d\n", dev_info);
	dev_info = 0;
	rc = ioctl(fd, SET_GET_DEV_INFO, &dev_info);
	if (rc < 0) {
		printf("failed to perform ioctl operation\n");
		close(fd);
		return -EINVAL;
	}
	printf("reseting device info %d\n", dev_info);
	close(fd);

	return 0;
}
