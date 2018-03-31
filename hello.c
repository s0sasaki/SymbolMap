#include <stdlib.h>

int global_val = 5;
int global_arr[1000] = {1,2,3};
const int global_const_val = 5;
const int global_const_arr[1000000] = {1,2,3};
int global_empty_val;
int global_empty_arr[2000000];
char  global_char_arr[] = "global_char_arr";
char *global_char_p     = "global_char_p";

int global_func(int x){
    return x + 1;
}

int main(){
    int local_val = 1;
    int local_arr[10000] = {1,2,3};
    const int local_const_val = 1;
    const int local_const_arr[10000] = {1,2,3};
    int local_empty_val;
    int local_empty_arr[2000000];
    char  local_char_arr[] = "local_char_arr";
    char *local_char_p     = "local_char_p";
    int *local_heap;
    //local_val = global_func(global_val);
    //global_empty_arr[0] = 3;
    local_heap = malloc(100000);
    sleep(10000);
    free(local_heap);
    return 0;
}
