#------------------------------------------------------------------------------
# Makefile for IntegerQueue ADT
# IntegerQueue.c
# Baladithya Balamurugan
# CruzId: bbalamur
# Class: CSE-15-1
# Date: 12/03/19
#------------------------------------------------------------------------------

CRUZID         = bbalamur
CLASSNAME      = cse015-pt.f19
ASSIGNMENT     = pa4
CLIENT          = Simulation
CLIENT2         = IntegerQueueTest
ADT1            = IntegerQueue
ADT2            = Job
SOURCE          = $(CLIENT).c
OBJECT          = $(CLIENT).o
SOURCE2         = $(CLIENT2).c
OBJECT2         = $(CLIENT2).o
ADT1_SOURCE     = $(ADT1).c
ADT1_OBJECT     = $(ADT1).o
ADT1_HEADER     = $(ADT1).h
ADT2_SOURCE     = $(ADT2).c
ADT2_OBJECT     = $(ADT2).o
ADT2_HEADER     = $(ADT2).h
COMPILE         = gcc -c -std=c99 -Wall
LINK            = gcc -o
REMOVE          = rm -f
MEMCHECK        = valgrind --leak-check=full --show-leak-kinds=all
SUBMIT         = submit $(CLASSNAME) $(ASSIGNMENT)
FILES          = $(ADT1_SOURCE) $(ADT2_SOURCE) $(SOURCE) $(SOURCE2) $(ADT1_HEADER) $(ADT2_HEADER) Makefile README 


$(CLIENT) : $(OBJECT) $(ADT1_OBJECT) $(ADT2_OBJECT) $(CLIENT2)
	$(LINK) $(CLIENT) $(OBJECT) $(ADT1_OBJECT) $(ADT2_OBJECT) 

$(CLIENT2) : $(OBJECT2) $(ADT1_OBJECT) 
	$(LINK) $(CLIENT2) $(OBJECT2) $(ADT1_OBJECT)

$(OBJECT2) : $(SOURCE2) $(ADT1_HEADER) 
	$(COMPILE) $(SOURCE2)

$(OBJECT) : $(SOURCE) $(ADT1_HEADER) $(ADT2_HEADER)
	$(COMPILE) $(SOURCE)

$(ADT1_OBJECT) : $(ADT1_SOURCE) $(ADT1_HEADER)
	$(COMPILE) $(ADT1_SOURCE)

$(ADT2_OBJECT) : $(ADT2_SOURCE) $(ADT2_HEADER)
	$(COMPILE) $(ADT2_SOURCE)

clean :
	$(REMOVE) $(CLIENT) $(OBJECT) $(ADT1_OBJECT) $(ADT2_OBJECT) $(CLIENT2) $(OBJECT2)

memcheck : $(CLIENT)
	$(MEMCHECK) $(CLIENT) test4

submit: $(FILES)
	$(SUBMIT) $(FILES)

check: 
	ls  /afs/cats.ucsc.edu/class/$(CLASSNAME)/$(ASSIGNMENT)/$(CRUZID)