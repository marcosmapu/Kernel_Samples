#include <linux/kernel.h>
#include <linux/module.h>

void meio(void)
{
	printk(KERN_INFO "por aqui o modulo passa no meio.c\n");
	return 0;
}
meio();