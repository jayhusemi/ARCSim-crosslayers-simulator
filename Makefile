CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra

# Add include search paths
INCLUDES = -I./cpu -I./mem -I./simulator

SRCS = \
    simulator/simulator.cpp \
    simulator/vcd.cpp \
    mem/memory.cpp \
    cpu/cpu.cpp \
    app/main.cpp

OBJS = $(SRCS:.cpp=.o)

TARGET = sim

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
