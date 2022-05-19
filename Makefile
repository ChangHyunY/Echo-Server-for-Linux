CC=g++
CFLAGS = -Wall $(shell mysql_config --cflags)
LIBS = $(shell mysql_config --libs)
OBJS = main.o Session.o FileIOSystem.o Database.o
TARGET=app.out

$(TARGET) : $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) -I/home/ubuntu/boost/boost_1_72_0 -L/home/ubuntu/boost/boost_1_72_0/stage/lib $(LIBS) -pthread

main.o : main.cpp 
	$(CC) -c main.cpp -I/home/ubuntu/boost/boost_1_72_0 -L/home/ubuntu/boost/boost_1_72_0/stage/lib

Session.o : Session.cpp
	$(CC) -c Session.cpp -I/home/ubuntu/boost/boost_1_72_0 -L/home/ubuntu/boost/boost_1_72_0/stage/lib

FileIOSystem.o : FileIOSystem.cpp
	$(CC) -c FileIOSystem.cpp

Database.o : Database.cpp
	$(CC) -c Database.cpp `mysql_config --cflags --libs`

clean:
	rm -f *.o
	rm -f app.out
