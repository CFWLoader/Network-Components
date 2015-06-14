CC = g++

FLAGS = -std=c++11 -g -Wall -c

TARGET_FILES = FileLogger.o

all: $(TARGET_FILES)

FileLogger.o: FileLogger.cpp FileLogger.h
	$(CC) -o $@ $(FLAGS) $<

clean:
	rm -rf *.o

cleanall:
	rm -rf $(TEST_FILES)
