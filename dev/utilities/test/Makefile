CC = g++

FLAGS = -std=c++11 -g -Wall

HEADERDIR = ..

TARGET_FILES = NoncopyableTest

all: $(TARGET_FILES)

NoncopyableTest: NoncopyableTest.cpp  $(HEADERDIR)/Noncopyable.hpp
	$(CC) -o $@ $< $(FLAGS)

clean:
	rm -rf *.o

cleanall:
	rm -rf *.o $(TARGET_FILES)
