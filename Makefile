CC = g++
CCFLAGS = -std=c++11
LIBS ?= -lpthread 

OBJS=client.o messenger.o
TARGET=test

$(TARGET): $(OBJS)
	$(CC) $(CCFLAGS) $(LIBS) -o $@ $(OBJS)

client.o: client.cpp messenger.h

messenger.o: messenger.cpp messenger.h