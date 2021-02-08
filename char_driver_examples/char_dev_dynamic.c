#include <linux/module.h>
#include <linux/version.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/cdev.h>

static dev_t lld_dev;
static int count = 1;
static struct cdev *dyn_cdev;


static int char_dyn_open(struct inode *inode, struct file *filp)
{
	pr_info("%s: function triggered\n", __func__);
	return 0;
}

static int char_dyn_release(struct inode *inode, struct file *filp)
{
	pr_info("%s: function triggered\n", __func__);
	return 0;
}

static ssize_t char_dyn_write(struct file *file, const char __user * userbuf,
			      size_t count, loff_t * f_pos)
{
	pr_info("%s: function triggered\n", __func__);
	pr_info("data wrote is: %s of len=%lu\n", userbuf, count);

	return count;
}

static ssize_t char_dyn_read(struct file *filp, char __user *userbuf,
			     size_t count, loff_t *f_pos)
{
	pr_info("%s: function triggered\n", __func__);
	return count;
}

static struct file_operations char_dyn_fops = {
	.owner	=	THIS_MODULE,
	.open	=	char_dyn_open,
	.read	=	char_dyn_read,
	.write	=	char_dyn_write,
	.release	=	char_dyn_release,
};

static int __init char_dyn_init(void)
{
	int rc = 0;
	int start_minor = 0;
	rc = alloc_chrdev_region(&lld_dev, start_minor, count, "LLD_Cdev");
	if (rc < 0) {
		pr_err("%s: could not allocate major number\n", __func__);
		return rc;
	}
	/*Allocate cdev instance */
	dyn_cdev = cdev_alloc(); 
	if (!dyn_cdev) {
		pr_err("falied to get cdev memory\n");
		return -ENOMEM;
	}

	/* initialize cdev with fops object */
	cdev_init(dyn_cdev, &char_dyn_fops);
	/* register cdev with vfs */
	rc = cdev_add(dyn_cdev, lld_dev, 1);
	if (rc < 0) {
		pr_err("failed to add to system\n");
		return rc;
	}

	pr_info("%s: char dynamic device %s is successfully added\n", __func__, "LLD_Cdev");
	return rc;
}

static void __exit char_dyn_exit(void)
{
	cdev_del(dyn_cdev);
	unregister_chrdev_region(lld_dev, count);
	pr_info("%s: char dynamice device unloaded successfully\n", __func__);
	return;
}

module_init(char_dyn_init);
module_exit(char_dyn_exit);

MODULE_AUTHOR("Ganji Aravind");
MODULE_DESCRIPTION("LLD: char driver dynamic registration example");
MODULE_LICENSE("GPL");
