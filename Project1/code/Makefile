#header file directory
IDIR=include

#header file names
_DEPS=vector_cls.hpp
DEPS=$(patsubst %,$(IDIR)/%,$(_DEPS))

#source file directory
SDIR=src

#object file directory
_ODIR=obj
ODIR=$(SDIR)/$(_ODIR)

#source (.cpp) file names
_SOURCESC=poisson.cpp
SOURCESC=$(patsubst %,$(SDIR)/%,$(_SOURCESC))
_OBJECTSC=$(_SOURCESC:.cpp=.o)
OBJECTSC=$(patsubst %,$(ODIR)/%,$(_OBJECTSC))

#c++ compiler to be used
CC=g++

#Executable name
EXECUTABLE=poisson_solve

#libraries to link
LIBS=

#compiler flags
CFLAGS=-I$(IDIR)

$(ODIR)/%.o: $(SOURCESC) $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(EXECUTABLE):$(OBJECTSC)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o $(IDIR)/*~ $(EXECUTABLE) $(SDIR)/*~ /*~
