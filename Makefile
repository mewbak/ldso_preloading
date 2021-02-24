all:
	gcc -g -static interp.c iter.c /opt/elfmaster/lib/libelfmaster.a -o interp
	cp interp linker/
tests:
	gcc -Wl,--dynamic-linker=\/home\/elfmaster\/git\/ldso_preloading\/linker\/interp test.c -o test

clean:
	rm -f interp
