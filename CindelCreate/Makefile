

CC = g++
CFLAGS = -std=c++11

all:CINDEL_CREATE

toolFunction.o : toolFunction.cpp tool.h BaseClass.h
	$(CC) $(CFLAGS) -c toolFunction.cpp

main.o : main.cpp
	$(CC) $(CFLAGS) -c main.cpp

CINDEL_CREATE: main.o toolFunction.o
	$(CC) $(CFLAGS) -o CINDEL_CREATE main.o toolFunction.o

clean :
	rm main.o toolFunction.o 
