#include <stdio.h>

#define CALL(fn,arg)	{ ret_t r = { CALL, { { fn, arg } } }; return r; }
#define RET(rv)		{ ret_t r = { RETURN, { .retval = rv } }; return r; }

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
		};
		int retval;
	};
};

//static unsigned long callcnt = 0;


// library code:

int run_trampoline( ret_t action )
{
	while( CALL == action.action ) {
		action = action.fn( action.arg );
	};
	return action.retval;
}


// user code:

ret_t fn1( int );
ret_t fn2( int );

ret_t fn2( int arg )
{
	printf("2:%d\n", arg);
	CALL(fn1,arg+1);
}

ret_t fn1( int arg )
{
	printf("1:%d\n", arg);

	if (arg < 1000000) {
		CALL(fn2,arg+1);
	} else {
		RET(arg);
	}
}

int main()
{
	ret_t action = { CALL, { { &fn1, 0 } } };
	int retval = run_trampoline( action );

	printf("final return value: %d\n", retval);

	return 0;
}

