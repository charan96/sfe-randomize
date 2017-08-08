CC=gcc
CFLAGS=--std=c99 -D_GNU_SOURCE -Wall -Werror -g
PP=g++
PFLAGS=--std=c++11 -Wall -Werror -g  
CPFLAGS=--std=c++11 -Wall -g

iforest/C/%.o: iforest/C/%.c iforest/C/%.h 
	$(CC) $(CFLAGS) -c $< -o $@

cincl.o: iforest/C/common.o iforest/C/object.o iforest/C/strfun.o iforest/C/readwrite.o iforest/C/argparse.o iforest/C/argparse_iforest.o iforest/C/frames.o
	ld -r iforest/C/common.o iforest/C/object.o iforest/C/strfun.o iforest/C/readwrite.o iforest/C/argparse.o iforest/C/argparse_iforest.o iforest/C/frames.o -o cincl.o

iforest/%.o: iforest/%.cpp iforest/%.hpp
	$(PP) $(PFLAGS) -c $< -o $@

forest.o: iforest/Forest.o iforest/IsolationForest.o iforest/Tree.o iforest/utility.o
	ld -r iforest/Forest.o iforest/IsolationForest.o iforest/Tree.o iforest/utility.o -o forest.o

# iforest.exe: cincl.o Forest.o IsolationForest.o Tree.o utility.o  main.o
#	$(PP) $(PFLAGS) -o iforest.exe cincl.o Forest.o IsolationForest.o Tree.o utility.o  main.o 

# -------------------------------------------------------------------------------------

%.o: %.cpp
	$(PP) $(CPFLAGS) -c $< -o $@

all: cincl.o forest.o print_funcs.o utilities.o randomize-method.o main.o
	$(PP) $(CPFLAGS) -o exec_obj cincl.o forest.o print_funcs.o randomize-method.o utilities.o main.o
	# $(CPP) $(CPFLAGS) print_funcs.cpp utilities.cpp randomize-method.cpp main.cpp -o exec_obj
	./exec_obj

clean:
	rm -f *.o
	rm -f iforest/C/*.o
	rm -f iforest/*.o
	rm -f exec_obj

fresh: 
	make clean
	make all

run:
	./exec_obj
