CC = g++

FLAGS = -std=c++11 -g -Wall

HEADERDIR = ..

TARGET_FILES = NoncopyableTest AppendLoggerTest MutexLockTest

TEMPORARY_FILES_DIR = ./Temporary\ Datafiles

all: $(TARGET_FILES)

NoncopyableTest: NoncopyableTest.cpp  $(HEADERDIR)/Noncopyable.hpp
	$(CC) -o $@ $< $(FLAGS)

AppendLoggerTest: AppendLoggerTest.cpp $(HEADERDIR)/FileUtilities.o
	$(CC) -o $@ $< $(FLAGS)

MutexLockTest: MutexLockTest.cpp $(HEADERDIR)/MutexLock.o
	$(CC) -o $@ $^ $(FLAGS) -lpthread

clean:
	rm -rf *.o

cleanall:
	rm -rf *.o $(TARGET_FILES) $(TEMPORARY_FILES_DIR)/*
