IDIR=../include
DEPS=$(IDIR)/Solver.hpp
SOURCESC=Solver.cpp TestSolve.cpp
CC=g++
EXECUTABLE=TestSolve
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
	rm -f *.o $(IDIR)/*~ $(EXECUTABLE) *~
