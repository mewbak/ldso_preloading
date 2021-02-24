all:
	gcc -g -nostdlib interp.c iter.c -o interp
tests:
	gcc -Wl,--dynamic-linker=\/home\/elfmaster\/git\/ldso_preloading\/linker\/interp test.c -o test

clean:
	rm -f interp
