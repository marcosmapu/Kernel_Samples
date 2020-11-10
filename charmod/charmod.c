#include <linux/init.h>
#include <linux/module.h>
#include <linux/device.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/mutex.h>
#include <cdev.h>
#define DEVICE_NAME "test char"
#define CLASS_NAME "test"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("mmapurunga");
MODULE_DESCRIPTION("test char module");
MODULE_VERSION("1.0");

struct deviceData {
	struct cdev cdev;
};

static int devOpen(struct inode *inode, struct file *file){

};

static int devClose(struct inode *inode, struct file *file){

};

static ssize_t devRead(struct file *file, char __user *buf, ssize_t count, loff_t *offset){
	
};

static ssize_t devWrite(struct file *file, const char __user *buf, ssize_t count, loff_t *offset){
	
};

struct file_operations fops = 
{
	.open = devOpen,
	.read = devRead,
	.write = devWrite,
	.release = devClose,
};
