CXX = g++
CXXFLAGS = -std=c++14 -Wall -O -g -MMD -Werror=vla
SOURCES = $(wildcard *.cc)
OBJECTS = ${SOURCES:.cc=.o}
DEPENDS = ${OBJECTS:.o=.d}
EXEC = biquadris

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} -L/opt/homebrew/Cellar/libx11/1.8.10/lib -lX11

%.o: %.cc
	$(CXX) -c -o $@ $< $(CXXFLAGS)

-include ${DEPENDS}

.PHONY: clean

clean: 
	rm -f ${OBJECTS} ${DEPENDS} ${EXEC}
