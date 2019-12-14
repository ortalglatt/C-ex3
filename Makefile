all: NumericalAnalyzer

NumericalAnalyzer: NumericalAnalyzer.o libinfi.a
	gcc -Wall -Wextra -Wvla -std=c99 -lm -o NumericalAnalyzer NumericalAnalyzer.o libinfi.a

NumericalAnalyzer.o: NumericalAnalyzer.c
	gcc -Wall -Wextra -Wvla -std=c99 -lm -c NumericalAnalyzer.c

libinfi.a: infi.o
	ar rcs libinfi.a infi.o

infi.o: infi.c infi.h
	gcc -Wall -Wextra -Wvla -std=c99 -lm -c infi.c

PHONY: clean

clean:
	rm -f NumericalAnalyzer *.o *.a
