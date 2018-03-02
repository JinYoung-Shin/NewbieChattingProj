CC = g++
CFLAGS = -std=c++11
LIBS = -lpthread 

OBJS = server.o message.o 

TARGET = server

.SUFFIXES: .cpp .o

all: $(TARGET) 

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LIBS)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $<

server.o: server.cpp message.cpp CSheader.h
message.o: message.cpp message.h CSheader.h

clean:
	rm -rf $(OBJS) $(TARGET)