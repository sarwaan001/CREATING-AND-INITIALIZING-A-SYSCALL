# CREATING-AND-INITIALIZING-A-SYSCALL
Creating a linux Syscall. This repository has a patch file (.diff) and a description of creating and initializing a linux system call.

Implementation of syscall functions:
The way I implemented the new system calls is that I created the parameter int securitylevel in the task struct at /reptilian-kernel/include/linux/sched.h and initialized it to 0 (default value) in the file /reptilian-kernel/include/linux/init_task.h. This was edited because it will create each process with the parameter and set it to 0 by default.
Once the security level parameter is created, I created the securitylevel folder in /reptilian- kernel/securitylevel. This folder is where I implemented sys_set_security_level and sys_get_security_level functions for the syscall. These functions are implemented in securitycall.h and securitycall.c.
The functions were created to determine whether the user was a superuser (e.g. uses the sudo command) by the userid being 0 and make sure processes cannot edit other processes with a higher security level. A conditional statement was created to make sure a child process could not edit a user process’s security level if the child process and the user process has the same level, however a user process can be able to edit a child process’s security level if the user process has the same security level as the child process.
Once these functions were created, the functions were added to the reptilian- kernel/arch/x86/entry/syscalls/syscall_64.tbl syscall_64.tbl list: sys_get_security_level as syscall 332 and sys_set_security_level as syscall 333. This table refers to the syscall header in reptilian- kernel/include/linux/syscalls.h, where the functions are added to the implementation. By keeping these two files consistent, the syscall function will work.
In order to make the syscall functions to compile in the kernel, the reptilian-kernel/Makefile was edited to include the target securitylevel/:
core -y += kernel/ mm/ fs/ ipc/ security/ crypto/ block/ securitylevel/
Also another Makefile was created in reptilian-kernel/securitylevel/Makefile to include the command:
obj-y:=listProcessInfo.o
These commands in the make synchronize the Makefiles with one another to compile the syscall functions.

Implementation of Library functions:
The library functions are created in the reptilian-kernel/securitylevel folder. The file that it was created in was the securitylevel.h file (for abstraction) and the securitylevel.c file. The library function implements a get_security_level function and a set_security_level function which both utilize the system calls that were just created. A makefile was created aswell.

Implementation of the Harness functions:
The harness functions are created in the same file as the library functions and are formatted according to the project specifications. The get and set harness functions returns an array of the get and set library function. The interpretation function prints a statement of interpretation of the return value of the parameter.

Testing:
All testing is done in the usr/rep/src folder where the following commands are done:
cc -o getlevel getlevel.c -I reptilian-kernel/ -L ./reptilian-kernel/securitylevel/ -lsecuritylevel cc -o setlevel setlevel.c -I reptilian-kernel/ -L ./reptilian-kernel/securitylevel/ -lsecuritylevel cc -o securitytest securitytest.c -I reptilian-kernel/ -L ./reptilian-kernel/securitylevel/ - lsecuritylevel
cc -o harnesstest harnesstest.c -I reptilian-kernel/ -L ./reptilian-kernel/securitylevel/ - lsecuritylevel
sudo ./securitytest
sudo ./harnesstest
Please test the following files in the kernel folder: usr/rep/src/reptilian-kernel/ if using: cc -o program_name sourcefile.c -L ./ securitylevel -lsecuritylevel
