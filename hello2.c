#include <linux/init.h>
#include <linux/module.h>
#include <linux/printk.h>
#include <linux/list.h>
#include <linux/slab.h>
#include <linux/ktime.h>

#include "hello1.h"

MODULE_AUTHOR("Kaprarenko Dmytro IO-12");
MODULE_DESCRIPTION("Hello, world in Linux Kernel Training Lab4");
MODULE_LICENSE("Dual BSD/GPL");

// How many times the string should be printed
static unsigned int amount = 1;
module_param(amount, uint, S_IRUGO);
MODULE_PARM_DESC(amount, "Output amount");


static int __init hello2_init(void)
{
	ktime_t before, after;

	before = ktime_get();

	print_hello(amount);

	after = ktime_get();

	pr_info("Time in hello2: %lld ns\n", ktime_to_ns(ktime_sub(after, before)));

	return 0;
}

static void __exit hello2_exit(void)
{
	exit_hello();
}

module_init(hello2_init);
module_exit(hello2_exit);
