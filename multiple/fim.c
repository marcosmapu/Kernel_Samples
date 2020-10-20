#include <linux/kernel.h>
#include <linux/module.h>

void cleanup_module()
{
	printk(KERN_INFO "aqui termina o modulo em fim.c\n");
}