matrix-text: main.c matrix.h
	cc -o matrix-test main.c -lm

clean:
	rm matrix-test
