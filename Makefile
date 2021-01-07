.PHONY: clean

CC=clang++
FLAGS=--std=c++17 -O2

example:
	$(CC) $(FLAGS) example.cc -o example && ./example && python plot_hull.py

clean:
	rm -f *.txt example
