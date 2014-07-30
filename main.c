#include <stdlib.h>
#include <stdio.h>
#include <setjmp.h>


#define LAMBDA(b)	b

#define CALL(fn,k)	fn(k)

#define CALLCC(fn)	{ jmp_buf k; int r = setjmp( k ); if ( ! r ) { fn( k, n ); } }

#define CONT		jmp_buf

//#define CALLCONT(k,rv)	longjmp(k,1)
#define CALLCONT(k,rv)	k(rv)


struct _cont_t;

typedef void (*contfn_t)( struct _cont_t* );

typedef struct _cont_t {
	contfn_t kfn;
	float arg;
} cont_t;

/*
struct _trampoline_t {
	void (*callback)();
};
*/


void func1( cont_t* k )
{
	printf( "func1\n" );

	cont_t nextk = { k->kfn, k->arg + 1.1 };
	k->kfn( &nextk );
}

void func2( cont_t* k )
{
	printf( "func2\n" );

	cont_t nextk = { k->kfn, k->arg + 2.2 };
	k->kfn( &nextk );
}

void func3( cont_t* k )
{
	printf( "func3\n" );

	cont_t nextk = { k->kfn, k->arg + 3.3 };
	k->kfn( &nextk );
}


void f1contfn( cont_t* k )
{
	printf( "%.2f\n", k->arg );
	exit( 1 );
}

void f2contfn( cont_t* k )
{
	cont_t k1 = { f1contfn, k->arg };
	func1( &k1 );
}

void f3contfn( cont_t* k )
{
	cont_t k2 = { f2contfn, k->arg };
	func2( &k2 );
}


int main( int argc, char* argv[] )
{
	printf( "this program should print 7.6f as a result and exit with status 1\n\n" );

	// do this in CPS:
	// func1( func2( func3( 1.0 ) ) );
	cont_t k3 = { f3contfn, 1.0 };
	func3( &k3 );

	printf( "this should never be printed!\n" );

	return 0;
}

