#------------------------------------------------------------------------------
# Makefile for HashTables ADT
# Dictionary.c
# Baladithya Balamurugan
# CruzId: bbalamur
# Class: CSE-15-1
# Date: 12/06/19
#------------------------------------------------------------------------------

CRUZID         = bbalamur
CLASSNAME      = cse015-pt.f19
ASSIGNMENT     = pa5
CLIENT         = DictionaryTest
ADT            = Dictionary
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

clean :
	$(REMOVE) $(CLIENT) $(OBJECT) $(ADT_OBJECT) 

memcheck : $(CLIENT)
	$(MEMCHECK) $(CLIENT)

submit: $(FILES)
	$(SUBMIT) $(FILES)

check: 
	ls  /afs/cats.ucsc.edu/class/$(CLASSNAME)/$(ASSIGNMENT)/$(CRUZID)