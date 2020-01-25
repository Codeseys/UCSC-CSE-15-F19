#------------------------------------------------------------------------------
# Makefile for SortStrings.c
# Baladithya Balamurugan
# CruzId: bbalamur
# Class: CSE-15-1
# Date: 12/05/19
#------------------------------------------------------------------------------

CRUZID         = bbalamur
CLASSNAME      = cse015-pt.f19
ASSIGNMENT     = lab5
PROGRAM_NAME = SortStrings
FLAGS        = -std=c99 -Wall
SOURCE       = $(PROGRAM_NAME).c
OBJECT       = $(PROGRAM_NAME).o
EXEBIN       = $(PROGRAM_NAME)
SUBMIT         = submit $(CLASSNAME) $(ASSIGNMENT)
FILES          = $(SOURCE) Makefile README 


$(EXEBIN) : $(OBJECT)
	gcc -o $(EXEBIN) $(OBJECT)

$(OBJECT) : $(SOURCE)
	gcc -c $(FLAGS) $(SOURCE)

clean :
	rm $(EXEBIN) $(OBJECT)

memcheck : $(EXEBIN)
	valgrind --leak-check=full $(EXEBIN) in myout

submit: $(FILES)
	$(SUBMIT) $(FILES)

check: 
	ls  /afs/cats.ucsc.edu/class/$(CLASSNAME)/$(ASSIGNMENT)/$(CRUZID)