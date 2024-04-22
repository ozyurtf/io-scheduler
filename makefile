CFLAGS=-g 
CXXFLAGS=-std=c++11
CC=g++-12

iosched: iosched.cpp
	$(CC) $(CXXFLAGS) iosched.cpp -o iosched

clean:
	rm -f iosched *~

check_version:
	$(CC) --version


