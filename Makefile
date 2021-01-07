.PHONY: clean

CC=clang++ --std=c++2a

example:
	$(CC) example.cc -o example && ./example && python plot_hull.py

clean:
	rm -f *.txt example
