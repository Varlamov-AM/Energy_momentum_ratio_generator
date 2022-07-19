CC = g++
CFLAGS = -Wall -g -c -o
LDFLAGS = `root-config --cflags` `root-config --libs`
SOURCEDIR = ../src/
SOURCES = $(SOURCEDIR)main.cpp $(SOURCEDIR)configuration.cpp $(SOURCEDIR)smearP.cpp $(SOURCEDIR)smearE.cpp
CONFSOURCES = ../Conf_creator.py
OBJECTS = $(SOURCES:.cpp=.o)
EX = Energy_momentum_ratio_generator


%.o: %.cpp
	$(CC) $(CFLAGS) $@ -c $<  $(LDFLAGS)

all:$(EX) 

$(EX): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@.exe $(LDFLAGS) 
	make clean

config_file:
	python3 $(CONFSOURCES)

clean:
	rm $(SOURCEDIR)*.o 
