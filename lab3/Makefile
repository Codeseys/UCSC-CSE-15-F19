#------------------------------------------------------------------------------
# Makefile for IntegerStackTest.c
# Subset.c
# Baladithya Balamurugan
# CruzId: bbalamur
# Class: CSE-15-1
# Date: 11/5/19
#------------------------------------------------------------------------------

CRUZID         = bbalamur
CLASSNAME      = cse015-pt.f19
ASSIGNMENT     = lab3
CLIENT         = IntegerStackTest
ADT            = IntegerStack
SOURCE         = $(CLIENT).c
OBJECT         = $(CLIENT).o
ADT_SOURCE     = $(ADT).c
ADT_OBJECT     = $(ADT).o
ADT_HEADER     = $(ADT).h
COMPILE        = gcc -c -std=c99 -Wall
LINK           = gcc -o
REMOVE         = rm -f
MEMCHECK       = valgrind --leak-check=full
SUBMIT         = submit $(CLASSNAME) $(ASSIGNMENT)
FILES          = $(ADT_SOURCE) $(SOURCE) $(ADT_HEADER) Makefile README

$(CLIENT) : $(OBJECT) $(ADT_OBJECT) 
	$(LINK) $(CLIENT) $(OBJECT) $(ADT_OBJECT) 

$(OBJECT) : $(SOURCE) $(ADT_HEADER) 
	$(COMPILE) $(SOURCE)

$(ADT_OBJECT) : $(ADT_SOURCE) $(ADT_HEADER)
	$(COMPILE) $(ADT_SOURCE)

format: 
	clang-format -i $(SOURCE) $(ADT_SOURCE)

clean :
	$(REMOVE) $(CLIENT) $(OBJECT) $(ADT_OBJECT) 

memcheck : $(CLIENT)
	$(MEMCHECK) $(CLIENT)

submit: $(FILES)
	$(SUBMIT) $(FILES)
