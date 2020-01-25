#------------------------------------------------------------------------------
# Makefile for any C program
#------------------------------------------------------------------------------
CRUZID         = bbalamur
CLASSNAME      = cse015-pt.f19
ASSIGNMENT     = lab4
PROGRAM_NAME = ArithmeticOperations
FLAGS        = -std=c99 -Wall
SOURCE       = $(PROGRAM_NAME).c
OBJECT       = $(PROGRAM_NAME).o
EXEBIN       = $(PROGRAM_NAME)
MEMCHECK     = valgrind --leak-check=full
SUBMIT       = submit $(CLASSNAME) $(ASSIGNMENT)
FILES        = $(SOURCE) Makefile README

$(EXEBIN) : $(OBJECT)
	gcc -o $(EXEBIN) $(OBJECT)

$(OBJECT) : $(SOURCE)
	gcc -c $(FLAGS) $(SOURCE)

clean :
	rm $(EXEBIN) $(OBJECT)

memcheck : $(EXEBIN)
	valgrind --leak-check=full $(EXEBIN) in1

submit: $(FILES)
	$(SUBMIT) $(FILES)

format: 
	clang-format -i $(SOURCE)

check: 
	ls  /afs/cats.ucsc.edu/class/$(CLASSNAME)/$(ASSIGNMENT)/$(CRUZID)