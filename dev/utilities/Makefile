CC = g++

FLAGS = -std=c++11 -g -Wall -c

TARGET_FILES = FileUtilities.o

all: $(TARGET_FILES)

FileUtilities.o: FileUtilities.cpp FileUtilities.h
	$(CC) -o $@ $(FLAGS) $<

clean:
	rm -rf *.o

cleanall:
	rm -rf $(TARGET_FILES)
