CXX = g++

CXXFLAGS = -Wall -Wextra -std=c++20 -Iassets

LIBS = -lsfml-graphics -lsfml-window -lsfml-system

SRC = Engine/*.cpp UI/*.cpp

TARGET = Battleship

all:
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET) $(LIBS)

run:
	./$(TARGET)

clean:
	rm -f $(TARGET)
