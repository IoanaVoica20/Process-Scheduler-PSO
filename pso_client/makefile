client: main.o client.o menu.o
	g++ -L /home/ioana/parce main.o client.o menu.o -o client -l_parce

main.o: main.cpp client.h Menu.h
	g++ -c main.cpp -o main.o

client.o: client.cpp client.h
	g++ -c client.cpp -o client.o

menu.o: Menu.cpp Menu.h
	g++ -c 	Menu.cpp -o menu.o

clean: 
	rm *.o