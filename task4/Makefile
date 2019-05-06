CXX       = g++
CXXFLAGS  = --std=c++17 
LIBS      = -lpthread -lgtest
SRCS      = $(wildcard *.cpp) 
OBJS      = $(filter %.o,$(SRCS:.cpp=.o) $(SRCS:.cc=.o))

logger: $(OBJS)
	$(CXX) -g $(OBJS) -o $@ $(LIBS)  

%.o: %.cc 
	$(CXX) $(CXXFLAGS) -c $< -O3 -o $@

clean:
	@rm -f *.o
	@rm -f table

.PHONY: clean 