#include <linux/init.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/mm.h>


static void *ptr;
int init_module(void)
{
	pr_info("kmalloc init function\n");
	ptr = kmalloc(1024, GFP_KERNEL);
	if (!ptr) {
		pr_err("failed to allocate memory\n");
		return ENOMEM;
	}

	pr_info("kmalloc success: %p\n", ptr);
	strcpy(ptr, "Hello kmalloc content\n");

	return 0;
}



void cleanup_module(void)
{
	pr_info("kmalloc cleanup function\n");
	if (ptr) {
		pr_info("contents in memory are : %s\n", (char *)ptr);
		kfree(ptr);
	}
	return;
}

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Ganji Aravind");
MODULE_DESCRIPTION("example about kmalloc");


