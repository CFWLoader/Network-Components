CC = g++

FLAGS = -std=c++11 -g -Wall -c

TARGET_FILES = File.o

all: $(TARGET_FILES)

File.o: File.cpp File.h
	$(CC) -o $@ $(FLAGS) $<

clean:
	rm -rf *.o

cleanall:
	rm -rf $(TARGET_FILES)
