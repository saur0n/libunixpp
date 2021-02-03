################################################################################
#   libunix++: C++ wrapper for Linux system calls
#   Build rules
#   
#   © 2019—2021, Sauron
################################################################################

NAME=unix++
CC=g++
CXXFLAGS=-fPIC -std=gnu++11 -Os -Wall -Wextra -Wno-unused-parameter -g
SOURCES=*.cpp
HEADERS=*.hpp
OUTPUT=lib$(NAME).so
PLATFORM?=STD

all: $(OUTPUT) unittest

$(OUTPUT): $(SOURCES) $(HEADERS)
	$(CC) -shared $(CXXFLAGS) -DPLATFORM_$(PLATFORM) -o $@ $(SOURCES) -lrt

unittest: tests/main.cpp *.hpp *.cpp 
	$(CC) $(CXXFLAGS) -pthread -DPLATFORM_$(PLATFORM) -o $@ *.cpp tests/main.cpp -lrt

clean:
	rm -f *.o *.so

release: all
	strip $(OUTPUT)

install: all
	mv $(OUTPUT) /usr/lib64
	mkdir -p /usr/include/$(NAME)
	cp $(HEADERS) /usr/include/$(NAME)

.PHONY:
	all release install clean
