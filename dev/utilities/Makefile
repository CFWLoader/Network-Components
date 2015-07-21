CC = g++

FLAGS = -std=c++11 -g -Wall -c

TARGET_FILES = File.o MutexLock.o

all: $(TARGET_FILES)

File.o: File.cpp File.h
	$(CC) -o $@ $(FLAGS) $<

MutexLock.o: MutexLock.cpp MutexLock.h
	$(CC) -o $@ $(FLAGS) $<

clean:
	rm -rf *.o

cleanall:
	rm -rf $(TARGET_FILES)
