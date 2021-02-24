INTERP_PATH="\/home\/elfmaster\/git\/ldso_preloading\/interp"

all:
	gcc -g -nostdlib lp_interp.c lp_iter.c lp_libc.c -o lp_interp
tests:
	#gcc -Wl,--dynamic-linker=$(INTERP_PATH) test.c -o test

clean:
	rm -f interp
