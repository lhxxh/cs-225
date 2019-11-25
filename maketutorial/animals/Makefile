dog_program:dog.o main.o
	clang++ main.o dog.o -o dog_program
dog.o :dog.cpp dog.hpp
	clang++ -c dog.cpp
main.o:main.cpp
	clang++ -c main.cpp -o main.o
clean:
	rm dog_program *.o
