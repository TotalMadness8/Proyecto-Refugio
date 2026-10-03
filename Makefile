TARGET = main.exe

CXX = g++
CXXFLAGS = -Wall -std=c++17 -Iheaders

SRCS = main.cpp $(wildcard clases/*.cpp)

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(TARGET)

clean:
	del /Q $(TARGET)