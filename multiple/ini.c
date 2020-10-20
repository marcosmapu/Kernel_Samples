#include <linux/kernel.h>	
#include <linux/module.h>	

int init_module(void)
{
	printk(KERN_INFO "Aqui comeca o modulo em ini.c\n");
	return 0;
}