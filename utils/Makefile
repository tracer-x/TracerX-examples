
all: treecmp
	chmod +x rebuild.sh

test: all
	./treecmp test1 test2 | grep '1 0 15 3' > /dev/null
	./treecmp test2 test1 | grep '0 16 0 -1' > /dev/null

clean:
	rm -f *~ treecmp rebuild.sh

