vpath %.c        src
vpath %.cpp      src
vpath test_%.cpp test
vpath %.h        include
vpath %.hpp        include

CC = gcc
CPP = g++
OPTIONS = -s
INCLUDES = -I include 
CFLAGS = -Wall -pedantic ${MAKE_OPTIONS} ${OPTIONS}
LIBS = 
LFLAGS = ${LIBS} ${OPTIONS}

default: rebuild


PHONY: check_init_parameters
check_init_parameters:
ifneq ($(UNICODE),)
	$(eval CFLAGS=${CFLAGS} -D_UNICODE -DUNICODE)
	$(eval LFLAGS=-municode ${LFLAGS})
endif
-include check_init_parameters

rebuild: clean build
clean:
	rm -vf *.o Main

build: raytrace

raytrace: Main.o
	${CPP} -o $@ $^ ${LFLAGS} 

Main.o: Main.cpp
	${CPP} -c -o $@ $< ${CFLAGS} ${INCLUDES}
