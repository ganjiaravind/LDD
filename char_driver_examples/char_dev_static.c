#include <linux/module.h>
#include <linux/version.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/cdev.h>

#define MAJORNUM	190
#define	MINORNUM	0
#define	CHAR_DEV_NAME	"SLLD_Cdev"
static dev_t lld_dev;
static int count = 1;
static struct cdev *stat_cdev;


static int char_stat_open(struct inode *inode, struct file *filp)
{
	pr_info("%s: function triggered\n", __func__);
	return 0;
}

static int char_stat_release(struct inode *inode, struct file *filp)
{
	pr_info("%s: function triggered\n", __func__);
	return 0;
}

static ssize_t char_stat_write(struct file *file, const char __user * userbuf,
			      size_t count, loff_t * f_pos)
{
	pr_info("%s: function triggered\n", __func__);
	pr_info("data wrote is: %s of len=%lu\n", userbuf, count);

	return count;
}

static ssize_t char_stat_read(struct file *filp, char __user *userbuf,
			     size_t count, loff_t *f_pos)
{
	pr_info("%s: function triggered\n", __func__);
	return count;
}

static struct file_operations char_stat_fops = {
	.owner	=	THIS_MODULE,
	.open	=	char_stat_open,
	.read	=	char_stat_read,
	.write	=	char_stat_write,
	.release	=	char_stat_release,
};

static int __init char_stat_init(void)
{
	int rc = 0;
	lld_dev = MKDEV(MAJORNUM, MINORNUM);
	rc = register_chrdev_region(lld_dev, count, CHAR_DEV_NAME);
	if (rc < 0) {
		pr_err("%s: could not allocate major number\n", __func__);
		return rc;
	}
	/*Allocate cdev instance */
	stat_cdev = cdev_alloc(); 
	if (!stat_cdev) {
		pr_err("falied to get cdev memory\n");
		return -ENOMEM;
	}

	/* initialize cdev with fops object */
	cdev_init(stat_cdev, &char_stat_fops);
	/* register cdev with vfs */
	rc = cdev_add(stat_cdev, lld_dev, 1);
	if (rc < 0) {
		pr_err("failed to add to system\n");
		return rc;
	}

	pr_info("%s: char dynamic device %s is successfully added\n", __func__, "LLD_Cdev");
	return rc;
}

static void __exit char_stat_exit(void)
{
	cdev_del(stat_cdev);
	unregister_chrdev_region(lld_dev, count);
	pr_info("%s: char dynamice device unloaded successfully\n", __func__);
	return;
}

module_init(char_stat_init);
module_exit(char_stat_exit);

MODULE_AUTHOR("Ganji Aravind");
MODULE_DESCRIPTION("LLD: char driver static registration example");
MODULE_LICENSE("GPL");
