#include <linux/module.h>
#include <linux/init.h>

void (*sfptr)(int);
int (*gfptr)(void);

int init_module(void)
{
	pr_info("module dependecy kernel object\n");

	sfptr = __symbol_get("set_counter");
	if (sfptr)
		sfptr(200);
	else
		pr_err("unable to get symbol reference\n");

	gfptr = __symbol_get("get_counter");
	if (gfptr)
		pr_info("counter value is %d\n", gfptr());
	else
		pr_err("unable to get symbol reference\n");

	return 0;
}

void cleanup_module(void)
{
	pr_info("unloading module dependecy kernel object\n");
	if (gfptr)
		__symbol_put("get_counter");
	if (sfptr)
		__symbol_put("set_counter");
	return;
}

MODULE_AUTHOR("Ganji Aravind");
MODULE_DESCRIPTION("Accessing Exported Function");
MODULE_LICENSE("GPL");
