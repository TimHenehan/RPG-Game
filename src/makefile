CC=g++
CFLAGS=-c -std=c++11
LDFLAGS=
LIBS=-lsfml-system  -lsfml-window  -lsfml-audio  -lsfml-graphics
SOURCES=main.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=../Game.out

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@ $(LIBS)

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@
clean:
	rm -rf *o $@
