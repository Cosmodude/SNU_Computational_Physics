CXX = g++
CXXFLAGS = -Wall -O2
SOURCES = task1.cpp task3.cpp task4.cpp  # Add all your source files here

# Create a list of targets by removing the file extension
TARGETS = $(foreach src,$(SOURCES),$(basename $(src)))

# Generate a list of object files
OBJECTS = $(SOURCES:.cpp=.o)

all: $(TARGETS) $(OBJECTS)

%: %.o
        $(CXX) $(CXXFLAGS) -o $@ $<

%.o: %.cpp
        $(CXX) $(CXXFLAGS) -c $< -o $@

clean:
        rm -f $(TARGETS) $(OBJECTS)



