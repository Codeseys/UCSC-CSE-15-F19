#---------------------------------------------------
# Makefile for Subset.c with macros
#---------------------------------------------------
CRUZID = bbalamur
CLASSNAME = cse015-pt.f19
ASSIGNMENT = pa1
EXEBIN = Subset
SOURCES = $(EXEBIN).c
OBJECTS = $(EXEBIN).o
FLAGS = -std=c99 -Wall
FILES = $(SOURCES) Makefile README
SUBMIT = submit $(CLASSNAME) $(ASSIGNMENT)
DEBUG_FILE = $(EXEBIN)_test.txt

$(EXEBIN) : $(OBJECTS)
	gcc -o $(EXEBIN) $(OBJECTS)
$(OBJECTS) : $(SOURCES)
	gcc -c $(FLAGS) $(SOURCES)
clean :
	rm -f $(EXEBIN) $(OBJECTS) *$(DEBUG_FILE)
submit: $(FILES)
	$(SUBMIT) $(FILES)
check: 
	ls  /afs/cats.ucsc.edu/class/$(CLASSNAME)/$(ASSIGNMENT)/$(CRUZID)
format: 
	clang-format -i $(SOURCES)
cleanTest:
	#cleans only degub output files
	rm -f *$(DEBUG_FILE)
test: 
	#generates test case outputs in text files
	$(MAKE) clean
	$(MAKE)
	echo "TestCase: 10 3" >> 10_3_$(DEBUG_FILE)
	./$(EXEBIN) 10 3 >> 10_3_$(DEBUG_FILE)
	echo "TestCase: 20 15" >> 20_15_$(DEBUG_FILE)
	./$(EXEBIN) 20 15 >> 20_15_$(DEBUG_FILE)
	echo "TestCase: 20 16" >> 20_16_$(DEBUG_FILE)
	./$(EXEBIN) 20 16 >> 20_16_$(DEBUG_FILE)
	echo "TestCase: 4 2" >> 4_2_$(DEBUG_FILE)
	./$(EXEBIN) 4 2 >> 4_2_$(DEBUG_FILE)
	echo "TestCase: 5 3" >> 5_3_$(DEBUG_FILE)
	./$(EXEBIN) 5 3 >> 5_3_$(DEBUG_FILE)
	echo "TestCase: 9 4" >> 9_4_$(DEBUG_FILE)
	./$(EXEBIN) 9 4 >> 9_4_$(DEBUG_FILE)
