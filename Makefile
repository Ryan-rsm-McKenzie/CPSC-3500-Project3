#Makefile

OBJS = main.o Bottleneck.o TrafficDirector.o TrafficSimulator.o Util.o Vehicle.o
CC = g++
CFLAGS = -pthread -c -std=c++11
LFLAGS = -std=c++11

p3: $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o p3

main.o: main.cpp Bottleneck.h TrafficDirector.h TrafficSimulator.h Util.h Vehicle.h
	$(CC) $(CFLAGS) main.cpp

Bottleneck.o: Bottleneck.cpp Bottleneck.h Singleton.h
	$(CC) $(CFLAGS) Bottleneck.cpp

TrafficDirector.o: TrafficDirector.cpp TrafficDirector.h Singleton.h Util.h
	$(CC) $(CFLAGS) TrafficDirector.cpp

TrafficSimulator.o: TrafficSimulator.cpp TrafficSimulator.h Singleton.h
	$(CC) $(CFLAGS) TrafficSimulator.cpp

Util.o: Util.cpp Util.h
	$(CC) $(CFLAGS) Util.cpp

Vehicle.o: Vehicle.cpp Vehicle.h Util.h
	$(CC) $(CFLAGS) Vehicle.cpp

clean:
	\rm *.o p3
