
appname := PROI_3

CXX := g++
CXXFLAGS := -std=c++11 -Wall -g

srcfiles := $(shell find . -maxdepth 1 -name "*.cpp")
objects  := $(patsubst %.cpp, %.o, $(srcfiles))

POSTFLAGS := -lncurses

all: $(appname)

$(appname): $(objects)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $(appname) $(objects) $(LDLIBS) $(POSTFLAGS)

clean:
	    rm *.o
