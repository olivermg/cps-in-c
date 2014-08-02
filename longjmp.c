#include <stdio.h>
#include <setjmp.h>

static long idx = -1;
jmp_buf ks[2000000];

void func( jmp_buf k )
{
	printf( "XXXXXXXXXXXXXX\n" );

	if ( ! setjmp( ks[++idx] ) ) {
		func( ks[idx] );
	}

	//longjmp( k, 1 );
}

int main( int argc, char* argv[] )
{
	func( ks[0] );

	return 0;
}

