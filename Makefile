#Makefile

OBJS = main.o Bottleneck.o TrafficDirector.o TrafficSimulator.o Util.o Vehicle.o
CC = g++
CFLAGS = -c -std=c++11
LFLAGS = -std=c++11

p3: $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o p3

main.o: main.cpp Bottleneck.h TrafficDirector.h TrafficSimulator.h Util.h Vehicle.h
	$(CC) $(CFLAGS) main.cpp

Bottleneck.o: Bottleneck.cpp Singleton.h
	$(CC) $(CFLAGS) Bottleneck.cpp

TrafficDirector.o: TrafficDirector.cpp Singleton.h Util.h
	$(CC) $(CFLAGS) TrafficDirector.cpp

TrafficSimulator.o: TrafficSimulator.cpp Singleton.h
	$(CC) $(CFLAGS) TrafficSimulator.cpp

Util.o: Util.cpp
	$(CC) $(CFLAGS) Util.cpp

Vehicle.o: Vehicle.cpp Util.h
	$(CC) $(CFLAGS) Vehicle.cpp

clean:
	\rm *.o p3
