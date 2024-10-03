#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int function_add(int a,int b)
{
    int c = a + b;
    return c;
}

int main() {
    if (fork() == 0)
        printf("HC: hello from child\n");
    else {
        printf("HP: hello from parent\n");
        wait(NULL);
        printf("CT: child has terminated\n");
    }
    printf("Bye\n");
    return 0;
}
