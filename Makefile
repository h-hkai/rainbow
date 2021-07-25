test: log.o util.o
	g++ -g -o test test.cpp util.o log.o -std=c++0x

log.o: log.h log.cpp
	g++ -c log.cpp -std=c++0x

util.o: util.h util.cpp
	g++ -c util.cpp -std=c++0x

clean:
	rm test
