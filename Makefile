CC=g++
CFLAGS=-g

Execute: main.o System.o hierarchy.o Users.o Bets.o
	$(CC) $(CFLAGS) main.o System.o hierarchy.o Users.o Bets.o -o Execute

main.o: main.cc
	$(CC) $(CFLAGS) -c main.cc -o main.o

System.o: System.cc
	$(CC) $(CFLAGS) -c System.cc -o System.o

hierarchy.o: hierarchy.cc
	$(CC) $(CFLAGS) -c hierarchy.cc -o hierarchy.o

Users.o: Users.cc
	 $(CC) $(CFLAGS) -c Users.cc -o Users.o

Bets.o: Bets.cc
	$(CC) $(CFLAGS) -c Bets.cc -o Bets.o

.PHONY: clean

clean:
	rm -f main.o System.o hierarchy.o Users.o Bets.o Execute
