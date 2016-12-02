OBJs =  Heaptree.cpp Stack.o Queue.o main.o

finalproject: $(OBJs)
	g++ -std=c++11 -Wall -g $(OBJs) -o finalproject 

Stack.o: Stack.cpp Stack.h
	g++ -std=c++11 -Wall -g -c Stack.cpp

Queue.o: Queue.cpp Queue.h
	g++ -std=c++11 -Wall -g -c Queue.cpp

Heaptree.o: Heaptree.cpp Heaptree.h
	g++ -std=c++11 -Wall -g -c Heaptree.cpp

clean:
	rm -f *.o
	rm -fr finalproject.dSYM
	rm -f *.exe

run:	clean finalproject 
	./finalproject FinalData250.txt
	#./finalproject
