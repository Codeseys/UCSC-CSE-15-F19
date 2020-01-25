#---------------------------------------------------
# Makefile for Queens.c with macros
#---------------------------------------------------
CRUZID = bbalamur
CLASSNAME = cse015-pt.f19
ASSIGNMENT = pa2
EXEBIN = Queens
SOURCES = $(EXEBIN).c
OBJECTS = $(EXEBIN).o
FLAGS = -std=c99 -Wall
FILES = $(SOURCES) Makefile 
SUBMIT = submit $(CLASSNAME) $(ASSIGNMENT)

$(EXEBIN) : $(OBJECTS)
	gcc -o $(EXEBIN) $(OBJECTS)
$(OBJECTS) : $(SOURCES)
	gcc -c $(FLAGS) $(SOURCES)
clean :
	rm -f $(EXEBIN) $(OBJECTS)
submit: $(FILES)
	$(SUBMIT) $(FILES)
check: 
	ls  /afs/cats.ucsc.edu/class/$(CLASSNAME)/$(ASSIGNMENT)/$(CRUZID)
format: 
	clang-format -i $(SOURCES)
memcheck:
	valgrind --leak-check=full $(EXEBIN) 8
