#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/slab.h>
#include <linux/gfp.h>


struct our_kmem {
	int a;
	char b;
};

struct kmem_cache *kcache;
void *object;

static int __init kmem_init(void)
{
	kcache = kmem_cache_create("example_cache", sizeof(struct our_kmem), 0,
				    SLAB_RED_ZONE, NULL); //last field is constructor handler
	if (!kcache) {
		pr_err("failed to create cache\n");
		return -ENOMEM;
	}

	object = kmem_cache_alloc(kcache, GFP_KERNEL);
	if (!object) {
		pr_err("failed to allocate memory\n");
		kmem_cache_destroy(kcache);
		return -ENOMEM;
	}

	pr_info("success: Got it and object is %p\n", object);
	return 0;
}

static void __exit kmem_exit(void)
{
	pr_info("unloading the kmem example module\n");
	kmem_cache_free(kcache, object);
	kmem_cache_destroy(kcache);
}
module_init(kmem_init);
module_exit(kmem_exit);

MODULE_AUTHOR("Ganji Aravind");
MODULE_DESCRIPTION("kmem_cache example");
MODULE_LICENSE("GPL");
