CXX=g++
CXXFLAGS=-std=c++14 -Wall -g -MMD -Werror=vla
EXEC=watan
OBJECTS=main.o board.o completion.o criterion.o dice.o fair.o goal.o loaded.o observer.o player.o resource.o state.o student.o subject.o textdisplay.o tile.o type.o
DEPENDS=${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}

.PHONY: clean
