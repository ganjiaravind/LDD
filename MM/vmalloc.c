#include <linux/init.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/mm.h>
#include <linux/vmalloc.h>


static void *ptr;
int init_module(void)
{
	pr_info("vmalloc init function\n");
	ptr = vmalloc(500);
	if (!ptr) {
		pr_err("failed to allocate memory\n");
		return ENOMEM;
	}

	pr_info("vmalloc success: %p\n", ptr);
	return 0;
}



void cleanup_module(void)
{
	pr_info("vmalloc cleanup function\n");
	if (ptr)
		vfree(ptr);
	return;
}

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Ganji Aravind");
MODULE_DESCRIPTION("example about vmalloc");


