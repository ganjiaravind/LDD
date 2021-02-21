#include <linux/module.h>
#include <linux/init.h>
#include <linux/interrupt.h>

static int irq = 1, dev_id = 10;
static irqreturn_t my_irq_handler(int num, void *dev)
{
	pr_info("%s function\n", __func__);
	return IRQ_NONE;
}

static __init int sample_init(void)
{
	int ret;
	pr_info("%s function\n", __func__);
	ret = request_irq(irq, my_irq_handler, IRQF_SHARED, "sample_interrupt",
			  &dev_id);
	if (ret < 0) {
		pr_err("failed to register irq on line %d\n", irq);
		return ret;
	}
	pr_info("successfully registered irq on line %d\n", irq);
	return ret;
}

static __exit void sample_exit(void)
{
	pr_info("%s function\n", __func__);
	synchronize_irq(irq);
	free_irq(irq, &dev_id);
}

module_init(sample_init);
module_exit(sample_exit);

MODULE_AUTHOR("Ganji Aravind");
MODULE_DESCRIPTION("Test Interrupt sample code");
MODULE_LICENSE("GPL");
