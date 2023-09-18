#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

int
sys_fork(void)
{
	return fork();
}

int
sys_exit(void)
{
	exit();
	return 0;  // not reached
}

int
sys_wait(void)
{
	return wait();
}

int
sys_kill(void)
{
	int pid;

	if(argint(0, &pid) < 0)
		return -1;
	return kill(pid);
}

int
sys_getpid(void)
{
	return myproc()->pid;
}

int
sys_sbrk(void)
{
	int addr;
	int n;

	if(argint(0, &n) < 0)
		return -1;
	addr = myproc()->sz;
	if(growproc(n) < 0)
		return -1;
	return addr;
}

int
sys_sleep(void)
{
	int n;
	uint ticks0;

	if(argint(0, &n) < 0)
		return -1;
	acquire(&tickslock);
	ticks0 = ticks;
	while(ticks - ticks0 < n){
		if(myproc()->killed){
			release(&tickslock);
			return -1;
		}
		sleep(&ticks, &tickslock);
	}
	release(&tickslock);
	return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
	uint xticks;

	acquire(&tickslock);
	xticks = ticks;
	release(&tickslock);
	return xticks;
}

int
sys_share_mem(void)
{
	struct proc *p = myproc();
	char *name;
	int sz;
	void *addr;
	int flag = 0;
	int struct_idx = -1;
	int i;

	if(argstr(0, &name) < 0 || argint(2, &sz) < 0 || argptr(1, &addr, sz) < 0)
		return -1;

	for(i = 0; i < 10; i++){
		if(strncmp(p->shared[i].name, name, 20) == 0)
				return -2;
		if(p->shared[i].sz == 0){
			safestrcpy(p->shared[i].name, name, 20*sizeof(char));
			p->shared[i].addr = addr;
			p->shared[i].sz = sz;
			flag = 1;
			struct_idx = i;
			break;
		}
	}

	if(flag == 0)
		return -3;
	else {
		cprintf("%s\n", p->shared[i].name);
		cprintf("%p\n", p->shared[i].addr);
		cprintf("%d\n", p->shared[i].sz);
		return struct_idx;
	}
}

int
sys_get_shared(void)
{
	struct proc *p = myproc();
	char *name;
	int *addr;
	uint i, flag = 0;

	if(argstr(0, &name) < 0 || argint(1, &addr) < 0)
		return -1;

	for(i = 0; i < 10; i++){
		if(strncmp(p->shared[i].name, name, 20) == 0){
			flag = 1;
			break;
		}
	}

	if(flag == 0)
		return -2;

	*addr = p->shared[i].addr;
	
	cprintf("Vrednost addr promenljive shared strukture u get_shared: %p\n", p->shared[i].addr);
	cprintf("Vrednost prosledjene addr promenljive u get_shared: %p\n", *addr);

	return 0;
}
