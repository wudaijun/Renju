SRC=src/model/*.cpp src/controller/*.cpp src/view/*.cpp
INCLUDE_DIR=./src

all:
	g++ -std=c++11 $(SRC) src/main.cpp -I$(INCLUDE_DIR) -o demo

test_evaluator:
	g++ -std=c++11 $(SRC) src/test/*.cpp -I$(INCLUDE_DIR) -o demo

