CXX = g++
CXXFLAGS = -Wall -Wextra -Wconversion -Wshadow -pedantic -std=gnu++17

# Define the default target (the first target in the Makefile).
all: problemA

# Compile the C++ source file with the specified flags.
%.out: %.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

# Clean up generated files.
clean:
	rm *.out

# Phony target to ensure 'clean' is not considered a file.
.PHONY: clean
