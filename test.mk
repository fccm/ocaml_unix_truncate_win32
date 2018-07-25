all: test.opt

test_stubs.o: test_stubs.c
	ocamlopt -c $<

test.cmx: test.ml
	ocamlopt -c $<

test.opt: test.cmx test_stubs.o
	ocamlopt -o test.opt test.cmx test_stubs.o

clean:
	rm -f test_stubs.o test.opt test.cmi test.cmx test.o

