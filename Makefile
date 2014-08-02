CC = clang
OPT = opt


.PHONY: clean


main: main.opt.bc
	$(CC) -Wall -g -o $@ $<

longjmp: longjmp.opt.bc
	$(CC) -Wall -g -o $@ $<

trampoline: trampoline.opt.bc
	$(CC) -Wall -g -o $@ $<


%.opt.bc: %.bc
	$(OPT) -mem2reg -tailcallelim -o $@ $<

%.bc: %.c
	$(CC) -Wall -g -emit-llvm -o $@ -c $<


clean:
	rm -vf *.o *.ll *.bc main longjmp trampoline

