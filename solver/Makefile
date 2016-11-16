CC=clang++ #Compiler
CFLAGS= -c -std=c++11   -fPIE   #Compiler Flags
DEFINES=-DENABLE_DELETE
INCPATH=

LDFLAGS= #Linker options

SOURCES= 	sokoban_solver.cpp \
					graph_search.cpp	\
					state_generator.cpp \
					heuristics.cpp \
					initializer.cpp

OBJECTS=$(SOURCES:.cpp=.o)  #Object files
EXECUTEABLE=solve #Output name
all: $(HEADERS) $(SOURCES) $(EXECUTEABLE)

$(EXECUTEABLE): $(OBJECTS)
	$(CC)    $(OBJECTS) -o $(EXECUTEABLE) $(LDFLAGS)


.cpp.o:
	$(CC)  $(CFLAGS) $(INCPATH) $(DEFINES)   $< -o $@


clean:  ; rm *.o $(EXECUTEABLE) $(MOCFILES) $(HEADERS)
