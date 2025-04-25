CXX = g++
CXXFLAGS = -std=c++17 -O2
TARGET = hello
SRC = main.cpp charger.cpp

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET)
