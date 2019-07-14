CC=g++
CFLAGS=$(shell pkg-config --cflags --libs opencv)

all: lense_correction

lense_correction: main.cpp correcter.cpp gui.cpp
	$(CC) -o lense_correction main.cpp correcter.cpp gui.cpp -std=c++11 $(CFLAGS)

run: lense_correction
	./lense_correction

clean:
	rm -rf *.o

mrproper: clean
	rm -rf hello