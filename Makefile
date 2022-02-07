CFLAGS = -std=c89 -O3 -Wall -Wextra -pedantic
COMPRESSOR = gzexe
STRIPPER = strip
STRIPFLAGS = -s

frus: frus.c
	$(CC) $(CFLAGS) -o frus frus.c

clean:
	rm -f *~ frus *.o*

optimize: frus clean
	$(STRIPPER) $<
	$(COMPRESSOR) $<
