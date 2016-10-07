
all: treecmp

test: all
	./treecmp test1 test2 | grep '2 0' > /dev/null
	./treecmp test2 test1 | grep '0 16' > /dev/null

clean:
	rm -f *~ treecmp

