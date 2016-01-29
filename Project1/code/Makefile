#Write programs to compile under SOURCESC
SOURCESC=poisson.cpp
#Executable name
EXECUTABLE=poisson_solve
OBJECTSC=$(SOURCESC:.cpp=.o)
#c++ compiler to be used
CC=g++
#compiler flags
CFLAGS=

all: $(EXECUTABLE) $(SOURCESC)

$(EXECUTABLE):$(OBJECTSC)
	$(CC) $(OBJECTSC) -o $@

.cpp.o:
	$(CC) -c $(CFLAGS) $< -o $@

.PHONY: clean

clean:
	rm -f $(EXECUTABLE) *.o *~
