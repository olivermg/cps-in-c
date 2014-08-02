#include <stdio.h>


#define REG(NAME)	_r_ ## NAME
#define CALL(FN,N)	{ _r_n = N; _r_fn = FN; return; }



typedef void (*contfn_t)();


static int _r_n;
static int _r_result;
static contfn_t _r_fn;


/*
void func()
{
	printf( "arg:%.3f\n", REG( arg ) );

	CALL( func, REG( arg ) + 1.1 );
}
*/

void fib()
{
	int n = REG( n );
	printf( "fib(%d)\n", n );

	if ( n <= 1 ) {
		CALL( NULL, REG( result ) + 1 );
	} else {
		CALL( fib, n - 2 );
		int r1 = REG( result );
		CALL( fib, n - 1 );
		int r2 = REG( result );
		REG( result ) = r1 + r2;
	}
}

int main( int argc, char* argv[] )
{
	REG( fn ) = fib;
	REG( n ) = 8;
	REG( result ) = 0;

	while ( REG( fn ) ) {
		REG( fn )();
	}

	printf( "fn:%p, n:%d, result:%d\n", REG( fn ), REG( n ), REG( result ) );

	return 0;
}

