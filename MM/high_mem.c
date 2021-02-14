#include <linux/module.h>
#include <linux/mm.h>
#include <linux/slab.h>
#include <linux/highmem.h>


struct page *pages;
static void *kptr;

int  init_module(void)
{
	pages = alloc_pages(__GFP_HIGHMEM, 2);
	if (!pages) {
		pr_err("unable to allocate requested pages\n");
		return ENOMEM;
	}

	kptr = kmap(pages);
	strcpy((char *)kptr ,"Hi Page how are you\n");

	pr_info("sucessfull init module\n");
	return 0;
}

void cleanup_module(void)
{
	pr_info("page contents are: %s\n", (char *)kptr);
	kunmap(pages);
	__free_pages(pages, 2);
	pr_info("unloading high memory example module\n");
}

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Ganji Aravind");
MODULE_DESCRIPTION("Example about High Memory");
