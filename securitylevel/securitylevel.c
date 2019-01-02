#include <stdlib.h>
#include <stdio.h>
#include <linux/kernel.h>
#include <sys/syscall.h>
#include <unistd.h>
#include "securitylevel.h"


//Library Functions
int set_security_level(int pid, int new_level) {
    long temp = syscall(332, pid, new_level);
    int temp2 = (int)temp;
    if(temp2 == new_level) {
        return new_level;
    }
    return -1;
}

int get_security_level(int pid) {
    long temp = syscall(333, pid);
    int finally = (int)temp;
    return finally;
}

//Harness Functions
int* retrieve_set_security_params (int pid, int new_level) {
    int *params = malloc (sizeof(int) * 4);
    params[0] = 332;
    params[1] = 2;
    params[2] = pid;
    params[3] = new_level;
    return params;
}


int* retrieve_get_security_params(int pid) {
    int *params = malloc (sizeof(int) * 3);
    params[0] = 333;
    params[1] = 1;
    params[2] = pid;
    return params;
}


int interpret_set_security_result (int ret_value) {
    if(ret_value == -1) {
        printf("Error in changing the security level.\n");
        return ret_value;
    }
    if(ret_value == 0) {
        printf("The security level is now 0.\n");
        return ret_value;
    }
    if(ret_value > 0) {
        printf("The security level was changed to be %d\n.", ret_value);
        return ret_value;
    }
    return -1;
}


int interpret_get_security_result (int ret_value) {
    if(ret_value == -1) {
        printf("Error in changing the security level.\n");
        return ret_value;
    }
    if(ret_value == 0) {
        printf("The security level is 0.\n");
        return ret_value;
    }
    if(ret_value > 0) {
        printf("The security level is %d\n", ret_value);
        return ret_value;
    }
    else return -1;
}


