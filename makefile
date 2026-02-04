CXX      := g++
CXXFLAGS := -std=c++20 -Wall -Iinclude -O3
TARGET   := superpermutation
SOURCES  := src/main.cpp src/permutations.cpp

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: all clean
