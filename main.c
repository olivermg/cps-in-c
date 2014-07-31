#include <stdlib.h>
#include <stdio.h>
#include <setjmp.h>


//#define LAMBDA(b)	b

//#define CALL(fn,k)	fn(k)

#define CALLCC(fn,v,rv)	{ jmp_buf jk; cont_t k = { &jk, v, 0.0 }; int r = setjmp( jk ); if ( ! r ) { fn( &k ); } else { rv = k.ret; } }

//#define CONT		jmp_buf

#define CALLCONT(k,rv)	{ k->ret = rv; longjmp( *k->kj, 1 ); }
//#define CALLCONT(k,rv)	k(rv)

//static float _curretval;

struct _cont_t;

typedef void (*contfn_t)( struct _cont_t* );

typedef struct _cont_t {
	//contfn_t kfn;
	jmp_buf* kj;
	float arg;
	float ret;
} cont_t;

/*
struct _trampoline_t {
	void (*callback)();
};
*/


void func1( cont_t* k )
{
	printf( "func1\n" );

	//k->arg = k->arg + 1.1;
	//k->kfn( k );
	CALLCONT( k, k->arg + 1.1 );
}

void func2( cont_t* k )
{
	printf( "func2\n" );

	//k->arg = k->arg + 2.2;
	//k->kfn( k );
	CALLCONT( k, k->arg + 2.2 );
}

void func3( cont_t* k )
{
	printf( "func3\n" );

	//k->arg = k->arg + 3.3;
	//k->kfn( k );
	CALLCONT( k, k->arg + 3.3 );
}


/*
void f1contfn( cont_t* k )
{
	printf( "%.2f\n", k->arg );
	exit( 1 );
}

void f2contfn( cont_t* k )
{
	k->kfn = f1contfn;
	func1( k );
}

void f3contfn( cont_t* k )
{
	k->kfn = f2contfn;
	func2( k );
}
*/


int main( int argc, char* argv[] )
{
	printf( "this program should print 7.6f as a result and exit with status 1\n\n" );

	// do this in CPS:
	// func1( func2( func3( 1.0 ) ) );
	float ret;
	CALLCC( func3, 1.0, ret );
	CALLCC( func2, ret, ret );
	CALLCC( func1, ret, ret );
	printf( "R:%.2f\n", ret );
	exit( 1 );

	printf( "this should never be printed!\n" );

	return 0;
}

