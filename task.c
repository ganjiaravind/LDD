#include <linux/module.h>
#include <linux/init.h>
#include <linux/sched.h>
#include <asm/current.h>

static int __init task_init(void)
{
	pr_info("Caller Process Name %s\n", current->comm);
	pr_info("Caller Process id %ld\n",(long int)current->pid);
	pr_info("Task stack start address %p\n", current->stack);

	return 0;
}

static void __exit task_exit(void)
{
	pr_info("Caller Process Name %s\n", current->comm);
	pr_info("Caller Process id %ld\n",(long int)current->pid);

	return;
}

module_init(task_init);
module_exit(task_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Ganji Aravind");
MODULE_DESCRIPTION("LLD Task information");
