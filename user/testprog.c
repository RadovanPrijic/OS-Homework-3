#include "kernel/types.h"
#include "kernel/stat.h"
#include "user.h"

int
main(void)
{
    int a1 = 5;
    int a2 = 10;
    int *niz = malloc(100000*sizeof(int));
    int *ptr = niz;

    int pid;
    char *argv2[] = {"/bin/testprogchild", 0};

    ptr[0] = 1;
    ptr[1] = 2;
    ptr[2] = 3;

    printf("%d\n", share_mem("a1", &a1, sizeof(int)));
    printf("%d\n", share_mem("a2", &a2, sizeof(int)));
    printf("%d\n", share_mem("niz", &niz, 100000*sizeof(int)));

    pid = fork();

    if(pid == 0){
        exec("/bin/testprogchild", argv2);
    }

    wait();
	exit();
}