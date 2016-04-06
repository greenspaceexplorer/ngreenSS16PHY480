IDIR=include
SDIR=src
DEPS=$(wildcard $(IDIR)/*.h)
SOURCESC=$(wildcard $(SDIR)/*.C)
CC=g++
EXECUTABLE=SolarSolve
LIBS= -lgsl -lgslcblas

OBJECTSC=$(SOURCESC:.cpp=.o)

CFLAGS=-I$(IDIR) `root-config --cflags --glibs`

all: $(EXECUTABLE) $(SOURCESC) $(DEPS)

$(EXECUTABLE): $(OBJECTSC)
	$(CC) -o $@ $(OBJECTSC) $(CFLAGS) $(LIBS)

.cpp.o:
	$(CC) -c $(CFLAGS) $< -o $@


.PHONY: clean

clean:
	rm -f $(SDIR)/*.o $(IDIR)/*~ $(EXECUTABLE) $(SDIR)/*~ /*~ *~ *.csv *.pdf
