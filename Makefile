#Makefile for Budget Buddy
CC = g++
exe_file = budget_buddy
$(exe_file): implementation.o driver.o
	$(CC) -std=c++11 implementation.o driver.o -o $(exe_file)
implementation.o: implementation.cpp
	$(CC) -std=c++11 -c implementation.cpp
driver.o: driver.cpp
	$(CC) -std=c++11 -c driver.cpp

clean:
	rm -f *.out *.o budget_buddy
