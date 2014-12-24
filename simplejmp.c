#include <stdio.h>

#define DEFCALL(fn,arg)	(ret_t){ CALL, .call = { fn, arg } }
#define DEFRET(rv)		(ret_t){ RETURN, .retval = rv }

#define CALL(fn,arg)	return DEFCALL(fn,arg);
#define RET(rv)			return DEFRET(rv);

typedef struct _ret_t ret_t;
typedef ret_t (*func_p)( int );

typedef enum {
	CALL,
	RETURN
} action_t;

struct _ret_t {
	action_t action;
	union {
		struct {
			func_p fn;
			int arg;
		} call;
		int retval;
	};
};


//
// library code:
//

// trampoline runner function:
int run_trampoline( ret_t action )
{
	while ( CALL == action.action ) {
		action = action.call.fn( action.call.arg );
	};
	return action.retval;
}

// language runtime function for invoking closures etc.:
int invoke( func_p fn, int arg )
{
	// ...runtime logic to wrap arguments into environment, etc...

	return run_trampoline( DEFCALL( fn, arg ) );
}


//
// user code:
//

ret_t fn1( int );
ret_t fn2( int );

ret_t fn2( int arg )
{
	printf("2:%d\n", arg);
	CALL( &fn1, arg + 1 );
}

ret_t fn1( int arg )
{
	printf("1:%d\n", arg);

	if (arg < 1000000) {
		CALL( &fn2, arg + 1 );
	} else {
		RET( arg );
	}
}

int main()
{
	int retval = invoke( &fn1, 0 );

	printf("final return value: %d\n", retval);

	return 0;
}

