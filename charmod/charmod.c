#include <linux/init.h>
#include <linux/module.h>
#include <linux/device.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/mutex.h>
#include <cdev.h>

#define DEVICE_NAME "mapu char driver module sample"
#define CLASS_NAME "sample"
#define DEVICES	5


MODULE_LICENSE("GPL");
MODULE_AUTHOR("mmapurunga");
MODULE_DESCRIPTION("skeleton to char driver modules");
MODULE_VERSION("1.0");

struct deviceData 
{
	struct cdev cdev;
	int num;
	char status;
};

struct deviceData devs[DEVICES];

static dev_t deviceNumber;

static int devOpen(struct inode *inode, struct file *file)
{
	struct deviceData *devData;
	devData = container_of(inode->i_cdev, struct deviceData, cdev);
	file->private_data = devData;
};

static int devClose(struct inode *inode, struct file *file)
{
	return 0;
};

static ssize_t devRead(struct file *file, char __user *userBuf, ssize_t count, loff_t *offset)
{
	struct deviceData *devData = (struct deviceData *) file->private_data;
	ssize_t len = min(devData->size - *offset, size);
	
	if (len <= 0){
		return 0;
	}
	
		// read from devData->buffer to user buffer
		if (copy_to_user(userBuf, devData->buffer + *offset, len))
			return -EFAULT;
	
		*offset += len;
		return len;	
	
};

static ssize_t devWrite(struct file *file, const char __user *userBuf, ssize_t count, loff_t *offset)
{
		struct deviceData *devData = (struct deviceData *) file->private_data;
		ssize_t len = min(devData->size - *offset, size);
		
		if (len <= 0){
			return 0;
		}
		
		// read from user buffer to devData->buffer
		if (copy_from_user(userBuf, devData->buffer + *offset, len))
			return -EFAULT;
	
		*offset += len;
		return len;
};

struct file_operations fops = 
{
	.owner = THIS_MODULE,
	.open = devOpen,
	.read = devRead,
	.write = devWrite,
	.release = devClose,
};

static int __init char_init(void)
{
	int i, err;
	
	// Driver registration (allocating a major number and 'DEVICES' minor numbers)
	err = alloc_chrdev_region(&deviceNumber, 0, DEVICES, DEVICE_NAME);

	if (err < 0){
		// Driver registration error
		printk(KERN_DEBUG "Error registering device\n");
		return err;
	}
	
	for (i = 0; i < DEVICES; i++){
		// Initializing devices
		cdev_init(&devs[i].cdev, &fops);
		
		// Adding device to the kernel
		if (err = cdev_add(&devs[i].cdev, (deviceNumber + i), 1)){
				// Error adding device
				printk(KERN_DEBUG "Error adding device\n");
				return err;
		}		
	}
	
	printk(KERN_DEBUG "Char driver initialized\n");
	return 0;
}

static void __exit char_exit(void)
{
	int i;
	
	// deleting devices
	for (i = 0; i < DEVICES; i++){
			cdev_del(&devs[i].cdev);
	}
	
	// unregistering major number
	unregister_chrdev_region(deviceNumber, DEVICES);
	
	printk("Exiting driver\n");
}

module_init(char_init);
module_exit(char_exit);
