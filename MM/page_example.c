#include <linux/module.h>
#include <linux/mm.h>
#include <linux/slab.h>


struct page *pages;
static char *vptr;

int  init_module(void)
{
	pr_info("size of a page is %lu\n", PAGE_SIZE);
	pages = alloc_pages(GFP_KERNEL, 2);
	if (!pages) {
		pr_err("unable to allocate requested pages\n");
		return ENOMEM;
	}

	vptr = page_address(pages);

	strcpy(vptr ,"Hi Page how are you\n");

	pr_info("sucessfull init module\n");
	return 0;
}

void cleanup_module(void)
{
	if (vptr)
		pr_info("page contents are: %s\n", vptr);
	if (pages)
		__free_pages(pages, 2);
	pr_info("unloading page example module\n");
}

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Ganji Aravind");
MODULE_DESCRIPTION("Example about struct pages");
