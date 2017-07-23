all:
	g++ -std=c++11 print_funcs.cpp utilities.cpp randomize-method.cpp main.cpp -o exec_obj
	./exec_obj

clean:
	rm -f *.o
	rm -f exec_obj
