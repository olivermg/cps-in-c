#include <setjmp.h>
#include <stdio.h>

#define CALL(fn)	{ nextfn = &fn; return 1; }
#define RET()		return 0

typedef int (*func_p)();

//static jmp_buf jb;
static unsigned long callcnt = 0;
static func_p nextfn;


// library code:

/*
void call( func_p fn )
{
	if ( ! setjmp( jb ) ) {
		fn();
	}
}

void ret()
{
	longjmp( jb, 1 );
}
*/

void run_trampoline()
{
	int r = 0;

	do {
		r = nextfn();
	} while (r);
}


// user code:

int fn1();
int fn2();

int fn2()
{
	printf("2:%ld\n", callcnt++);
	CALL(fn1);
}

int fn1()
{
	printf("1:%ld\n", callcnt++);

	if (callcnt < 1000000) {
		CALL(fn2);
	} else {
		RET();
	}
}

int main()
{
	nextfn = &fn1;
	run_trampoline();

	return 0;
}

