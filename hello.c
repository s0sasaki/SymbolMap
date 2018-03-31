#include <stdlib.h>

int global_val = 5;
int global_arr[1000] = {1,2,3};
const int global_const_val = 5;
const int global_const_arr[10000] = {1,2,3};
int global_empty_val;
int global_empty_arr[2000000];
char  global_char_arr[] = "global_char_arr";
char *global_char_ptr   = "global_char_ptr";

int global_func(int x){
    return x + 1;
}

int main(){
    int local_val = 1;
    int local_arr[1000] = {1,2,3};
    const int local_const_val = 1;
    const int local_const_arr[10000] = {1,2,3};
    int local_empty_val;
    int local_empty_arr[2000000];
    char  local_char_arr[] = "local_char_arr";
    char *local_char_ptr   = "local_char_ptr";
    static int local_static_val = 1;
    static int local_static_empty_val;
    static const int local_static_const_val = 1;
    int *local_heap;
    local_heap = malloc(100000);
    sleep(10000);
    free(local_heap);
    return 0;
}
