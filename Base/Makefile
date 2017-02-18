.PHONY: all

FLAGS= -std=c++14 -Wall -Wextra

SRC=$(wildcard *.cpp)
OBJ = $(patsubst %.cpp, out/%.o, $(SRC))
HD = $(wildcard *.h)

all: pizza

pizza: $(OBJ)
	g++ $(FLAGS) $(OBJ) -o pizza

out/%.o : %.cpp $(HD)
	@mkdir -p out
	g++ $(FLAGS) -c $< -o $@

