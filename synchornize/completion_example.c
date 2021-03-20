#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/kthread.h>
#include <linux/completion.h>
#include <linux/delay.h>
#include <linux/slab.h>

struct task_struct *t1, *t2;
DECLARE_COMPLETION(syn_wait);

typedef struct {
	int a;
	int b;
}priv_data;
static priv_data *p;

int kthread_reader(void *arg)
{
	pr_info("%s: function and waiting for complete\n", __func__);
	wait_for_completion(&syn_wait);
	pr_info("Got comple signal, continuing for reading\n");
	if (p)
		pr_info("%s: read a = %d, b = %d\n", __func__, p->a, p->b);
	
	do_exit(0);
}

int kthread_writer(void *arg)
{
	pr_info("%s: function\n", __func__);
	if (!p) {
		pr_err("private date is NULL\n");
		return -EINVAL;
	}
	p->a = 10;
	p->b = 20;
	ssleep(20);
	pr_info("Send complete signal to the waiting threads\n");
	complete(&syn_wait);

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

	t2 = kthread_run(kthread_reader, NULL, "Kreader");
	if(IS_ERR(t2)){
                pr_err("%s: unable to start kernel thread\n",__func__);
		kfree(p);
                return PTR_ERR(t2);
        }

	t1 = kthread_run(kthread_writer, NULL, "Kwriter");
	if(IS_ERR(t1)){
                pr_err("%s: unable to start kernel thread\n",__func__);
		kfree(p);
                return PTR_ERR(t1);
        }
	return 0;
}

void kthread_exit(void)
{
	pr_info("%s: function\n", __func__);
	kfree(p);
	return;
}

module_init(kthread_init);
module_exit(kthread_exit);

MODULE_AUTHOR("Ganji Aravind");
MODULE_DESCRIPTION("Kernel wait for completion Example");
MODULE_LICENSE("GPL");
