#ifndef _IOCTL_EXAMPLE_H
#define _IOCTL_EXAMPLE_H

#ifdef __KERNEL__

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/types.h>
#include <linux/stat.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/ioctl.h>
#include <linux/slab.h>
#include <asm/uaccess.h>
#include <asm/errno.h>

struct float_n {
    unsigned long integral;
    unsigned long fraction;
};

static inline struct float_n float_n_construct(unsigned long n);
static inline unsigned long float_n_destruct(struct float_n* float_n);
static int on_open(struct inode* inode, struct file* file);
static int on_release(struct inode* inode, struct file* file);
static long on_unlocked_ioctl(struct file * file, unsigned int command, unsigned long arguemnt);
static int __init on_init(void);
static void on_exit(void);

#else

#include <sys/ioctl.h>

#endif

#define IOCTL_EXAMPLE_MAGIC_NUMBER '?'

#define IOCTL_EXAMPLE_ADDITION _IO(IOCTL_EXAMPLE_MAGIC_NUMBER, 0)

#define IOCTL_EXAMPLE_SET _IOW(IOCTL_EXAMPLE_MAGIC_NUMBER, 1, unsigned long)

#define IOCTL_EXAMPLE_GET _IOR(IOCTL_EXAMPLE_MAGIC_NUMBER, 2, unsigned long)

#define IOCTL_EXAMPLE_ADD _IOWR(IOCTL_EXAMPLE_MAGIC_NUMBER, 3, unsigned long)

#define IOCTL_EXAMPLE_LAST_IOCTL 3

#endif