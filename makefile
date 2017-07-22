run : $(OBJS)
	cc  -o run $(OBJS)

CC = gcc
FLAGS = -Wall -ansi -pedantic -I ./inc/
HPATH = ./inc/

OBJC =  parser.o logger.o logmngr.o vector.o

#Logger dynamic lib
liblogger.so: $(OBJC)
	$(CC) -shared -o liblogger.so $(OBJC) -lpthread

#parser
parser.o: parser.c $(HPATH)parser.h
	$(CC) -g -c -o  parser.o $(FLAGS) -fPIC parser.c

#logger
logger.o: logger.c $(HPATH)logger.h
	$(CC) -g -c -o  logger.o $(FLAGS) -fPIC logger.c

#logmngr
logmngr.o: logmngr.c $(HPATH)logmngr.h
	$(CC) -g -c -o  logmngr.o $(FLAGS) -fPIC logmngr.c

#vector
vector.o: vector.c $(HPATH)vector.h
	$(CC) -g -c -o  vector.o $(FLAGS) -fPIC vector.c

#clean
clean:
	rm -f $(OBJC) liblogger.so
