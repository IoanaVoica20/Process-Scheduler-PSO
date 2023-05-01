objs := main.o server.o interpreter.o Memory.o Process.o Scheduler.o FCFS.o SJF.o

server: $(objs)
	g++  -L /home/ioana/parce $(objs) -o server -l_parce 

main.o: main.cpp server.h
	g++ -c main.cpp -o main.o

interpreter.o: utile/interpreter.cpp utile/interpreter.h utile/Protocol.h stuff/Memory.h  algoritmi/Scheduler.h 
	g++ -c utile/interpreter.cpp -o interpreter.o

server.o: server.cpp server.h utile/interpreter.h 
	g++ -c server.cpp -o server.o  

Memory.o: stuff/Memory.cpp stuff/Memory.h
	g++ -c stuff/Memory.cpp -o Memory.o

Process.o: stuff/Process.cpp stuff/Process.h stuff/Memory.h server.h utile/Protocol.h
	g++ -c stuff/Process.cpp -o Process.o


Scheduler.o : algoritmi/Scheduler.cpp algoritmi/Scheduler.h utile/Protocol.h 
	g++ -c algoritmi/Scheduler.cpp -o Scheduler.o

FCFS.o: algoritmi/FCFS.cpp algoritmi/FCFS.h stuff/Process.h server.h stuff/Memory.h
	g++ -c algoritmi/FCFS.cpp -o FCFS.o

SJF.o: algoritmi/SJF.cpp algoritmi/SJF.h stuff/Process.h server.h stuff/Memory.h
	g++ -c algoritmi/SJF.cpp -o SJF.o

clean: 
	rm *.o