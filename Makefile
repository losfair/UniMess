all:
	make -C src

clean:
	find . -name *.o -exec rm '{}' ';'
