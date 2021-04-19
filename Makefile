CC=g++
CXXFLAGS=-g

OBJS = ./src/main_sllpolynomial.o

all: ${OBJS}
	$(CC) $(CXXFLAGS) -o main_sllpolynomial ${OBJS}

clean:
	rm main_sllpolynomial && cd src && rm -rf *.o
