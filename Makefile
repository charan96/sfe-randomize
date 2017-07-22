all:
	g++ -std=c++11 try-stl.cpp -o exec_obj
	./exec_obj

clean:
	rm -f exec_obj
