all:
	g++ -std=c++11 randomize-method.cpp -o exec_obj
	./exec_obj

clean:
	rm -f exec_obj
