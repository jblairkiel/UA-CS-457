OBJs =  main.o

finalproject: $(OBJs)
	g++ -std=c++11 -Wall -g $(OBJs) -o finalproject 

clean:
	rm -f *.o
	rm -fr finalproject.dSYM
	rm -f *.exe

run:	clean finalproject 
	./finalproject FinalData250.txt
	#./finalproject
