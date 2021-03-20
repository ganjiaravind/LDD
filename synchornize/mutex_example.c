#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/kthread.h>
#include <linux/delay.h>
#include <linux/mutex.h>
#include <linux/slab.h>

typedef struct {
	int a;
	int b;
} priv_data;

static priv_data *p;
struct task_struct *t1, *t2;
DEFINE_MUTEX(ms_lock);


int kthread_reader(void *arg)
{
	pr_info("%s: attempting to lock \n",__func__);
	mutex_lock(&ms_lock);
	pr_info("%s: read a = %d, b = %d\n", __func__, p->a, p->b);
	mutex_unlock(&ms_lock);

	do_exit(0);
}

int kthread_writer(void *arg)
{
	pr_info("Writer thread running and trying to acquire lock\n");
	mutex_lock(&ms_lock);
	pr_info("writer thread acquired lock and going to sleep\n");
	p->a = 10;
	ssleep(10);
	p->b = 20;
	pr_info("writer thread unlocking the mutex\n");
	mutex_unlock(&ms_lock);

	do_exit(0);
}

void data_init(priv_data * data)
{
	data->a = 0;
	data->b = 0;
	pr_info("%s: function and data initalized to zero\n", __func__);
}


int kthread_init(void)
{
	p = (priv_data *) kmalloc(sizeof(priv_data), GFP_KERNEL);

	if (!p) {
		pr_err("failed to allocate kernel memory\n");
		return -ENOMEM;
	}
	data_init(p);
	pr_info("%s: function and private data allocated %p\n", __func__, p);

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
	pr_info("%s: function done and writer and reader thread are running\n", __func__);

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
MODULE_DESCRIPTION("Kernel Mutex Interface Example");
MODULE_LICENSE("GPL");


