
#include<linux/kernel.h>
#include<linux/init.h>
#include<linux/sched.h>
#include<linux/syscalls.h>
#include "securitycall.h"
#include<linux/module.h>
#include<linux/proc_fs.h>
#include<linux/capability.h>
#include<linux/cred.h>

asmlinkage long sys_set_security_level(int pid, int new_level) {
    struct task_struct *task = current;
    int userid = task->cred->uid.val;
    long newlevel = (long)new_level;
    struct task_struct *processes;
    if (userid == 0) {
        for_each_process(processes) {
            if (processes->pid == pid) {
                processes->securitylevel = new_level;
                return newlevel;
            }
        }
    }    
    int userlevel = task->securitylevel;
    struct task_struct *processes2;
    for_each_process(processes2) {
        if (processes2->pid == pid) {
            if (userlevel == processes2->securitylevel && task->pid != processes2->pid) {
                return -1;
            }
            if (userlevel >= new_level) {
                processes2->securitylevel = newlevel;
                return newlevel;
            }
            
        }
    }
    return -1;
}

asmlinkage long sys_get_security_level(int pid) {
	struct task_struct *proces;
	for_each_process(proces) {
		if(proces->pid == pid) {
			return (proces->securitylevel);
		}
	}
	return -1;
}

