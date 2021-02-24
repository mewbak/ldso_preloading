all:
	gcc -g -static interp.c iter.c /opt/elfmaster/lib/libelfmaster.a -o interp
clean:
	rm -f interp
