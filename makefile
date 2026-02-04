CXX      := g++
CXXFLAGS := -std=c++20 -Wall -Iinclude -O3
TARGET   := bin/superpermutation
SOURCES  := $(wildcard src/*.cpp)

all: $(TARGET)

$(TARGET): $(SOURCES)
	@if not exist "bin" mkdir bin
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(TARGET)

clean:
	@if exist "bin" rmdir /s /q "bin"

.PHONY: all clean
