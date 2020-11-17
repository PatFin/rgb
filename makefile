all:default
default: cycle random cascade raindrop

rgb.o:rgb.h rgb.cpp
	g++ -c -std=c++11 -o rgb.o -Wall -l wiringPi -l pthread rgb.cpp

cycle.o:cycle.cpp
	g++ -c -std=c++11 -o cycle.o -Wall cycle.cpp

random.o:random.cpp
	g++ -c -std=c++11 -o random.o -Wall random.cpp

cascade.o:cascade.cpp
	g++ -c -std=c++11 -o cascade.o -Wall cascade.cpp

raindrop.o:raindrop.cpp
	g++ -c -std=c++11 -o raindrop.o -Wall raindrop.cpp

cycle: rgb.o cycle.o
	g++ -l wiringPi -l pthread -o cycle cycle.o rgb.o

cascade: cascade.o rgb.o
	g++ -l wiringPi -l pthread -o cascade cascade.o rgb.o

raindrop:raindrop.o rgb.o
	g++ -l wiringPi -l pthread -o raindrop raindrop.o rgb.o

random:random.o rgb.o
	g++ -l wiringPi -l pthread -o random random.o rgb.o

clean:
	rm -f rgb.o main.o cycle random cascade
