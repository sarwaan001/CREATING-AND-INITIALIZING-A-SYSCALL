int set_security_level(int pid, int new_level);
int get_security_level(int pid);
int* retrieve_set_security_params (int pid, int new_level);
int* retrieve_get_security_params(int pid);
int interpret_set_security_result (int ret_value);
int interpret_get_security_result (int ret_value);
