make: main.c note.c entry.c date.c utils.c 
	gcc -O3 main.c note.c entry.c date.c utils.c -o main

clean:
	rm main
