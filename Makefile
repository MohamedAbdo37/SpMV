CXX = g++

# -fopenmp     : Enable OpenMP (REQUIRED for the parallel part later)
CXXFLAGS = -I./include -O2 -Wall -fopenmp


SRCS = src/main.cpp src/utils.cpp src/spmv_serial.cpp src/spmv_parallel.cpp

TARGET = spmv_app


all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)