#include <linux/module.h>
#include <linux/init.h>
#include "mod.h"

int init_module(void)
{
	pr_info("module dependecy kernel object with header file\n");
	pr_info("calling get_counter %u\n", get_counter());
	set_counter(5000);
	pr_info("calling set_counter %u\n", get_counter());
	return 0;
}

void cleanup_module(void)
{
	pr_info("unloading module dependecy kernel object\n");
	return;
}

MODULE_AUTHOR("Ganji Aravind");
MODULE_DESCRIPTION("Accessing Exported Function example using header");
MODULE_LICENSE("GPL");
