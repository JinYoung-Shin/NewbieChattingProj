CC = g++
CFLAGS = -std=c++11
LIBS = -lpthread 
 
OBJS = client.o message.o messenger.o

TARGET = client

.SUFFIXES: .cpp .o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LIBS)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $<

client.o: client.cpp messenger.cpp messenger.h message.h
messenger.o: messenger.cpp messenger.h message.cpp CSheader.h
message.o: message.cpp message.h CSheader.h

clean:
	rm -rf $(OBJS) $(TARGET)