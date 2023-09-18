#include "kernel/types.h"
#include "kernel/stat.h"
#include "user.h"

int
main(void)
{
    void *addr1;
    void *addr2;
    void *addr3;

    int res1 = get_shared("a1", &addr1);
    printf("Rezultat f-je get_shared za addr1: %d\n", res1);
    int res2 = get_shared("a2", &addr2);
    printf("Rezultat f-je get_shared za addr2: %d\n", res2);
    int res3 = get_shared("niz", &addr3);
    printf("Rezultat f-je get_shared za addr3: %d\n", res3);
    
    printf("Vrednost addr1 u dete procesu: %p\n", addr1);
    printf("Vrednost addr2 u dete procesu: %p\n", addr2);
    printf("Vrednost addr3 u dete procesu: %p\n", addr3);

    printf("Dereferencirana vrednost a1 u dete procesu: %d\n", *(int *)addr1);
    printf("Dereferencirana vrednost a2 u dete procesu: %d\n", *(int *)addr2);
    printf("Dereferencirana vrednost niz[0] u dete procesu: %d\n", ((int *)addr3)[0]);
    printf("Dereferencirana vrednost niz[1] u dete procesu: %d\n", ((int *)addr3)[1]);
    printf("Dereferencirana vrednost niz[2] u dete procesu: %d\n", ((int *)addr3)[2]);
    
	exit();
}