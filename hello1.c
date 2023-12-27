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


struct my_struct {
	struct list_head list_node;     
	ktime_t timestamp;		// ktime_t field
};

// Declare a static variable for the head of the list
static LIST_HEAD(my_list_head);

int print_hello(unsigned int amount)
{
	int k;
	struct my_struct *entry;

	//Print the string based on the amount value
	pr_info("Amount of Hellos: %u\n", amount);

	if(amount == 0) {
		pr_warn("Warning: Parameter == 0", amount);
	}
	else if(amount >= 5 && amount <= 10) {
		pr_warn("Warning: 5 <= Parameter <= 10", amount);
	}
	else if(amount > 10) {
		pr_err("Error: Parameter > 10\n");
		BUG_ON(1);
	}

	for (k = 1; k <= amount; k++) {
		// Simulate kmalloc() for 5 element
		if (k == 5) {
			entry = NULL;
		} else {
			entry = kmalloc(sizeof(struct my_struct), GFP_KERNEL);
		}

		if (!entry) {
			pr_err("Error allocating memory for my_struct.\n");
			return -ENOMEM;
		}

		INIT_LIST_HEAD(&entry->list_node);
		entry->timestamp = ktime_get();// Set the timestamp

		// Add entry to the linked list
		list_add_tail(&entry->list_node, &my_list_head);
	
		// Print Hello, world! and time
		pr_info("Hello, World! Time in nanoseconds: %lld ns\n", ktime_to_ns(entry->timestamp));
	}

	return 0;
}
EXPORT_SYMBOL(print_hello);

void exit_hello(void)
{
	struct my_struct *entry, *tmp;

	// Iterate through the list
	list_for_each_entry_safe(entry, tmp, &my_list_head, list_node) {

		// Print time in nanoseconds
		pr_info("Goodbye, World! Time in nanoseconds: %lld ns\n", ktime_to_ns(entry->timestamp));

		// Remove the entry from the list
		list_del(&entry->list_node);

		// Free the allocated memory
		kfree(entry);
	}
}
EXPORT_SYMBOL(exit_hello);
