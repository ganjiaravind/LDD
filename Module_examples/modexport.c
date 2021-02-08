#include <linux/module.h>
#include <linux/init.h>

static int counter;

void set_counter(int value)
{
	counter = value;
}
EXPORT_SYMBOL_GPL(set_counter);

int get_counter(void)
{
	return counter;
}
EXPORT_SYMBOL_GPL(get_counter);

static int __init session_start(void)
{
	pr_info("%s: function\n", __func__);
	counter = 1000;
	return 0;
}

static void __exit session_close(void)
{
	pr_info("%s: counter %d\n", __func__, counter);
	return;
}

module_init(session_start);
module_exit(session_close);
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Module export example");
MODULE_AUTHOR("Ganji Aravind");
