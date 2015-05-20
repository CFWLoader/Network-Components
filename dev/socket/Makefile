CC = g++

TEST_FILES = test

FALGS = -std=c++11 -g -Wall

all: $(TEST_FILES)

test: test.cpp Socket.o
	$(CC) $(FLAGS) -o $@ $^

Socket.o: Socket.cpp Socket.h
	$(CC) $(FLAGS) -o $@ -c $<

clean:
	rm -rf *.o

cleanall:
	rm -rf *.o $(TEST_FILES)
