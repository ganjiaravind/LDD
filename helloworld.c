#include <linux/module.h>
#include <linux/init.h>

int init_module(void)
{
	printk(KERN_ALERT "Hello, World\n");
	return 0;
}

void cleanup_module(void)
{
	printk(KERN_ALERT "Goodbye\n");
	return;
}

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("LDD Helloworld session");
MODULE_AUTHOR("Ganji Aravind");
