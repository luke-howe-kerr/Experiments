all: main

main: main.cpp
	g++ -g main.cpp -o main

clean:
	rm -f main *.o *~