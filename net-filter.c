#include <linux/init.h>
#include <linux/module.h>
#include <linux/netfilter.h>

unsigned int counter = 0;
unsigned int nf_hookfn_package_counter(
        unsigned int hooknum,
        struct sk_buffer *skb,
        const struct net_device *in,
        const struct net_device *out,
        int(*okfn)(struct sk_buff*))
{
    counter ++;
    if(counter > 100)
    {
        printk("100 counter reach, reset\n");
        counter = 0;
    }
    return NF_ACCEPT;
}

static struct nf_hook_ops _hook_ops = {
    .hook = nf_hookfn_package_counter,
    .owner = THIS_MODULE,
    .pf = NFPROTO_IPV4,
    .hooknum = NF_INET_PRE_ROUTING,
    .priority = 0,
};

static int net_filter_test_init(void)
{
    printk(KERN_INFO "[init] now init the netfilter hook\n");
    int reg_result = nf_register_hook(&_hook_ops);
    printk(KERN_INFO "reg_result:%d\n", reg_result);
    return 0;
}

static void net_filter_test_exit(void)
{
    nf_unregister_hook(&_hook_ops);
    printk(KERN_INFO "[exit] unregister done:\n");
}


module_init(net_filter_test_init);
module_exit(net_filter_test_exit);

MODULE_AUTHOR("Johnzeng");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("A simple Hello World Module");
MODULE_ALIAS("A simple module");
