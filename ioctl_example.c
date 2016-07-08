#include "ioctl_example.h"

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Ivo Stratev (NoHomey)");

#define __NAME__ "ioctl_example"

#define _LOG_ERR(function) printk("Error: when calling %s\n", function)

#define _HANDLE_IF_ERR(return_value, function) \
if(return_value) { \
    _LOG_ERR(function); \
    on_exit(); \
    return 1; \
} \

static dev_t numbers;
static unsigned long tmp;
static struct float_n n_A;
static struct float_n n_B;
static struct float_n result;
static int in_use = 0;
static int major = -1;
static const int first_minor = 0;
static const unsigned int minor_count = 1;
static struct cdev* cdev = NULL;
static struct file_operations file_operations = {
    .owner = THIS_MODULE,
    .open = on_open,
    .release = on_release,
    .unlocked_ioctl = on_unlocked_ioctl
};

static inline struct float_n float_n_construct(unsigned long n) {
    struct float_n float_n;
    float_n.integral = n >> 16;
    float_n.fraction = n & 65535;
    return float_n;
}

static inline unsigned long float_n_destruct(struct float_n& float_n) {
    unsigned long n = float_n->integral << 16;
    n |= float_n->fraction;
    return n;
}

static int on_open(struct inode* inode, struct file* file) {
    if(in_use) {
        return -EBUSY;
    } else {
       in_use = 1; 
    }
    return 0;
}

static int on_release(struct inode* inode, struct file* file) {
    in_use = 0; 
    return 0;
}

static long on_unlocked_ioctl(struct file * file, unsigned int command, unsigned long argument) {
    if(_IOC_TYPE(command) != IOCTL_EXAMPLE_MAGIC_NUMBER) {
		printk("Error: ioctl magic number isn't device driver's one\n");
		return -ENOTTY;
	}
	if(_IOC_NR(command) > IOCTL_EXAMPLE_LAST_IOCTL) {
		printk("Error: ioctl command exceeds last implemented command\n");
		return -ENOTTY;
	}
    switch(command) {
        #define _IOCTL_EXAMPLE_INPUT() \
        return get_user(tmp, (unsigned long __user*)argument) \

        #define _IOCTL_EXAMPLE_OUTPUT() \
        return put_user(tmp, (unsigned long __user*)argument) \

        case IOCTL_EXAMPLE_SET: {
            
        }

        #undef _IOCTL_EXAMPLE_INPUT
        #undef _IOCTL_EXAMPLE_OUTPUT
    }
    return 0;
}

static int __init on_init(void) {
    printk("on_init\n");
    _HANDLE_IF_ERR(alloc_chrdev_region(&numbers, first_minor, minor_count, __NAME__), "alloc_chrdev_region");
    major = MAJOR(numbers);
    cdev = cdev_alloc();
    cdev->owner = THIS_MODULE;
    cdev->ops = &file_operations;
    _HANDLE_IF_ERR(cdev_add(cdev, numbers, minor_count), "cdev_add");
    return 0;
}

static void on_exit(void) {
    printk("on_exit\n");
    if(cdev) {
        cdev_del(cdev);
    }
    if(major > -1) {
        unregister_chrdev_region(numbers, minor_count);
    }
}


module_init(on_init);
module_exit(on_exit);

#undef __NAME__
#undef _LOG_ERR
#undef _HANDLE_IF_ERR