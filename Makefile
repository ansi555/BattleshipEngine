CXX = g++

CXXFLAGS = -Wall -Wextra -std=c++20 -Iassets -finput-charset=UTF-8 -fexec-charset=UTF-8

LIBS = -lsfml-graphics -lsfml-window -lsfml-system

SRC = main.cpp Engine/*.cpp UI/*.cpp

TARGET = Battleship

all:
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET) $(LIBS)

run:
	./$(TARGET)

clean:
	rm -f $(TARGET)
