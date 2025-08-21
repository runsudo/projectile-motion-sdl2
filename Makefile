build:
	gcc -Wall -std=c99 ./src/*.c -o main $(shell pkg-config --cflags --libs sdl2)
run:
	./main
clean:
	rm main