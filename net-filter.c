#include <linux/init.h>
#include <linux/module.h>

static int net_filter_test_init(void)
{
        printk(KERN_INFO "[init] Can you feel me?\n");
            return 0;
}

static void net_filter_test_exit(void)
{
        printk(KERN_INFO "[exit] Yes.\n");
}


module_init(net_filter_test_init);
module_exit(net_filter_test_exit);

MODULE_AUTHOR("Johnzeng");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("A simple Hello World Module");
MODULE_ALIAS("A simple module");
