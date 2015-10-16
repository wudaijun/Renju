SRC=src/*/*.cpp src/*.cpp
INCLUDE_DIR=./src

all:
	g++ -std=c++11 $(SRC) -I$(INCLUDE_DIR) -o demo

