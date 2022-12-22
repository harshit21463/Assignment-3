#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/unistd.h>
#include <linux/sched.h>
#include <linux/types.h>
#include <linux/syscalls.h>

MODULE_AUTH("Harshit");
MODULE_LICENSE("GPL");

int input = 0;

module_param(input,int,0);

static int  __init first_function(void){
    struct task_struct *kaam;
    process = pid_task(find_vpid(input),PIDTYPE_PID);

    if(!kaam){
        printk("Invalid Input\n");
        return -1;
    }

    printk("name of the process : %s\n",process->comm);
    printk("PID/UID: %d & %d\n", process->pid,process->cred->uid.val);
    printk("Group ID : %d\n",process->group_leader->pid);
    return 0;
}

static void __exit leaving(void){
    printk("system call close\n");
}

module_init(first_function);
module_exit(leaving);