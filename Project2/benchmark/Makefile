IDIR=include
SDIR=src
DEPS=$(wildcard $(IDIR)/*.hpp)
SOURCESC=$(wildcard $(SDIR)/*.cpp)
CC=g++
EXECUTABLE=SchrodSolve
LIBS= -lgsl -lgslcblas

OBJECTSC=$(SOURCESC:.cpp=.o)

CFLAGS=-I$(IDIR)

all: $(EXECUTABLE) $(SOURCESC) $(DEPS)

$(EXECUTABLE): $(OBJECTSC)
	$(CC) -o $@ $(OBJECTSC) $(CFLAGS) $(LIBS)

.cpp.o:
	$(CC) -c $(CFLAGS) $< -o $@


.PHONY: clean

clean:
	rm -f $(SDIR)/*.o $(IDIR)/*~ $(EXECUTABLE) $(SDIR)/*~ /*~ *~
