OBJS	= test.o
SOURCE	= test.cpp
HEADER	= 
OUT	= test
CC	 = g++
FLAGS	 = -g -c -Wall
LFLAGS	 = 

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

test.o: test.cpp
	$(CC) $(FLAGS) test.cpp 


clean:
	rm -f $(OBJS) $(OUT)