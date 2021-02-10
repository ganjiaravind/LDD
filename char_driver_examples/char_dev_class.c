#include <linux/module.h>
#include <linux/version.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/cdev.h>

#define	DEV_NAME	"chardev-0"
#define	CLASS_NAME	"TEST"
static dev_t lld_dev;
static int count = 1;
static struct cdev *dyn_cdev;
static struct class *classp;
static struct device *devp;


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

static struct file_operations char_dyn_fops = {
	.owner	=	THIS_MODULE,
	.open	=	dev_open,
	.read	=	dev_read,
	.write	=	dev_write,
	.release	=	dev_release,
};

static int __init class_init(void)
{
	int rc = 0;
	int start_minor = 0;
	rc = alloc_chrdev_region(&lld_dev, start_minor, count, "DLLD_Cdev");
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

	classp = class_create(THIS_MODULE, CLASS_NAME);
	if (IS_ERR(classp)) {
		pr_err("%s: failed to create class\n",__func__);
		rc = PTR_ERR(classp);
		goto free_cdev;
	}

	devp = device_create(classp, NULL, lld_dev, NULL, DEV_NAME);
	if (IS_ERR(devp)) {
		rc = PTR_ERR(devp);
		goto free_class;
	}
	pr_info("%s: class base char dynamic device %s is successfully added\n",
		__func__, DEV_NAME);
	return rc;

free_class:
	class_destroy(classp);
free_cdev:
	cdev_del(dyn_cdev);
	unregister_chrdev_region(lld_dev, count);
	return rc;
}

static void __exit class_exit(void)
{
	device_destroy(classp, lld_dev);
	class_destroy(classp);
	cdev_del(dyn_cdev);
	unregister_chrdev_region(lld_dev, count);
	pr_info("%s: class base char dynamice device unloaded successfully\n",
		__func__);
}

module_init(class_init);
module_exit(class_exit);

MODULE_AUTHOR("Ganji Aravind");
MODULE_DESCRIPTION("LLD: char driver dynamic registration with class example");
MODULE_LICENSE("GPL");
