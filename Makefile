CXX = g++
CXXFLAGS = -g -std=c++14 -Wall -Werror=return-type -Werror=uninitialized

TARGET = dsaproject2

SRCS = main.cpp simulation.cpp
OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -mconsole -o $(TARGET) $(OBJS)


main.o: main.cpp simulation.hpp
	$(CXX) $(CXXFLAGS) -c main.cpp

simulation.o: simulation.cpp simulation.hpp
	$(CXX) $(CXXFLAGS) -c simulation.cpp


clean:
	rm -f $(OBJS) $(TARGET)

rebuild: clean all

