#include <stdio.h>
#include <assert.h>

char* strcpy2(char* str_dest, char const* str_src) {
    assert(str_dest != NULL && str_src != NULL);

    char* address = str_dest;
    while ((*str_dest++ = *str_src++) != '\0') {
        ;
    }

    return address;
}

int main(int argc, char const *argv[]) {
    char* src = "hello strcpy";

    char buffer[100];

    strcpy2(buffer, src);

    printf("%s\n", buffer);

    char arr[20] = "hello world";
    strcpy2(arr, arr+1);
    printf("%s\n", arr);
    
    return 0;
}
