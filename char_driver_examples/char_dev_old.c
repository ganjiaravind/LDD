#include <linux/module.h>
#include <linux/version.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/cdev.h>

static int major = 0;


static int dev_open(struct inode *inode, struct file *filp)
{
	pr_info("%s: function triggered\n", __func__);
	return 0;
}

static int dev_release(struct inode *inode, struct file *filp)
{
	pr_info("%s: function triggered\n", __func__);
	return 0;
}

static ssize_t dev_write(struct file *file, const char __user * userbuf,
			      size_t count, loff_t * f_pos)
{
	pr_info("%s: function triggered\n", __func__);
	pr_info("data wrote is: %s of len=%lu\n", userbuf, count);

	return count;
}

static ssize_t dev_read(struct file *filp, char __user *userbuf,
			     size_t count, loff_t *f_pos)
{
	pr_info("%s: function triggered\n", __func__);
	return count;
}

static struct file_operations char_dev_fops = {
	.owner	=	THIS_MODULE,
	.open	=	dev_open,
	.read	=	dev_read,
	.write	=	dev_write,
	.release	= dev_release,
};

static int __init char_old_init(void)
{
	major = register_chrdev(major, "LLD_olddev", &char_dev_fops);
	if (major < 0) {
		pr_err("failed to acquire major number\n");
		return major;
	}

	pr_info("%s: module loaded successfully with major number %u\n", __func__, major);
	return 0;
}

static void __exit char_old_exit(void)
{
	unregister_chrdev(major, "LLD_olddev");
	pr_info("%s: module unloaded successfully\n", __func__);
	return;
}

module_init(char_old_init);
module_exit(char_old_exit);

MODULE_AUTHOR("Ganji Aravind");
MODULE_DESCRIPTION("LLD: char driver old format registration example");
MODULE_LICENSE("GPL");
