################################################################################
#   libunix++: C++ wrapper for Linux system calls
#   Build rules
#   
#   © 2019—2020, Sauron
################################################################################

NAME=unix++
CC=g++
CXXFLAGS=-fPIC -std=gnu++11 -Os -Wall -Wextra -Wno-unused-parameter -g
SOURCES=*.cpp
HEADERS=*.hpp
OUTPUT=lib$(NAME).so
PLATFORM?=STD

all: $(OUTPUT)

$(OUTPUT): $(SOURCES) $(HEADERS)
	$(CC) -shared $(CXXFLAGS) -DPLATFORM_$(PLATFORM) -o $@ $(SOURCES)

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
