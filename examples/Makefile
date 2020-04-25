all: sdelete

clean:
	rm -f sdelete

sdelete: sdelete.cpp
	gcc -Wall -Wextra -Os -o sdelete -lstdc++ -lunix++ sdelete.cpp

.PHONY: all clean
