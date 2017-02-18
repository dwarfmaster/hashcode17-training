.PHONY: all

FLAGS= -std=c++14 -Wall -Wextra

SRC=$(wildcard *.cpp)
OBJ = $(patsubst %.cpp, out/%.o, $(SRC))
HD = $(wildcard *.hpp)

all: pizza

pizza: $(OBJ)
	g++ $(FLAGS) -c -o coin.o ../coin.cpp
	g++ $(FLAGS) $(OBJ) -o pizza

out/%.o : %.cpp $(HD)
	@mkdir -p out
	g++ $(FLAGS) -c $< -o $@

