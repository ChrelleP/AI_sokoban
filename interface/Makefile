CC=clang++-3.5 #Compiler
CFLAGS= -c -std=c++11   -fPIE   #Compiler Flags
DEFINES=-DENABLE_DELETE
INCPATH=

LDFLAGS= #Linker options

SOURCES= solver_interface.cpp  #cpp files

OBJECTS=$(SOURCES:.cpp=.o)  #Object files
EXECUTEABLE=solver_interface #Output name
all: $(HEADERS) $(SOURCES) $(EXECUTEABLE)

$(EXECUTEABLE): $(OBJECTS)
	$(CC)    $(OBJECTS) -o $(EXECUTEABLE) $(LDFLAGS)


.cpp.o:
	$(CC)  $(CFLAGS) $(INCPATH) $(DEFINES)   $< -o $@


clean:  ; rm *.o $(EXECUTEABLE) $(MOCFILES) $(HEADERS)
