CXX = g++
CXXFLAGS = -Wall -std=c++11
TARGET = vending_machine
SRCS = VendingMachine.cpp Admin.cpp Inventory.cpp PaymentProcessor.cpp Product.cpp SalesData.cpp Transaction.cpp
OBJS = $(SRCS:.cpp=.o)

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: clean