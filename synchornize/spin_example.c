#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/kthread.h>
#include <linux/delay.h>
#include <linux/spinlock.h>
#include <linux/slab.h>

typedef struct {
	int a;
	int b;
	spinlock_t lock;
} priv_data;

static priv_data *p;
struct task_struct *t1, *t2;

int kthread_reader(void *arg)
{
	pr_info("%s: attempting to lock \n", __func__);
	spin_lock(&p->lock);
	pr_info("%s: read a = %d, b = %d\n", __func__, p->a, p->b);
	spin_unlock(&p->lock);
	do_exit(0);
}

int kthread_writer(void *arg)
{
	pr_info("writer thread trying to acquire the spin lock\n");
	spin_lock(&p->lock);
	pr_info("writer thread acquired the spin lock\n");
	p->a = 10;
	p->b = 20;
	pr_info("writer thread releasing the spin lock\n");
	spin_unlock(&p->lock);
	do_exit(0);
}

void data_init(priv_data * data)
{
	spin_lock_init(&data->lock);
	data->a = 0;
	data->b = 0;
	pr_info("%s: function successfully done\n", __func__);
}

int kthread_init(void)
{
	p = (priv_data *) kmalloc(sizeof(priv_data), GFP_KERNEL);
	if(IS_ERR(p)){
                pr_err("%s: unable to allocate memory\n",__func__);
                return PTR_ERR(p);
        }
	data_init(p);

	t1 = kthread_run(kthread_writer, NULL, "Kwriter");
	if(IS_ERR(t1)){
                pr_err("%s: unable to start kernel thread\n",__func__);
		kfree(p);
                return PTR_ERR(t1);
        }

	t2 = kthread_run(kthread_reader, NULL, "Kreader");
	if(IS_ERR(t2)){
                pr_err("%s: unable to start kernel thread\n",__func__);
		kfree(p);
                return PTR_ERR(t2);
        }

	pr_info("%s: function and writer thread and reader threads already running\n",
			__func__);
	return 0;
}

void kthread_exit(void)
{
	pr_info("%s: function\n", __func__);
	kfree(p);
}

module_init(kthread_init);
module_exit(kthread_exit);

MODULE_AUTHOR("Ganji Aravind");
MODULE_DESCRIPTION("Kernel spinlock Interface Example");
MODULE_LICENSE("GPL");
