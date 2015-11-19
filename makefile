CC=gcc
FLAG=-Wall -W
OBJ= dico.o main.o grille.o
OBJTEST= dico_test.o main_test.o grille_test.o
JOB= ./include/*.h
SRC=./src/
TEST=./src/tests/
all:ruzzle.exe test.exe clean doc

ruzzle.exe: ${OBJ}
	${CC} -o ./bin/ruzzle.exe ${OBJ} ${FLAG}

struct.o: ${SRC}struct.c ${JOB}
	${CC} -c ${SRC}struct.c ${FLAG} 

dico.o: ${SRC}dico.c
	${CC} -c ${SRC}dico.c ${FLAG} 

grille.o: ${SRC}grille.c
	${CC} -c ${SRC}grille.c ${FLAG} 

main.o: ${SRC}main.c ${JOB}
	${CC} -c ${SRC}main.c ${JOB} ${FLAG} 

test.exe: ${OBJTEST}
	${CC} -o ./tests/test.exe ${OBJTEST} ${FLAG} -lcunit

struct_test.o: ${TEST}struct_test.c ${JOB}
	${CC} -c ${TEST}struct_test.c ${FLAG} 

dico_test.o: ${TEST}dico_test.c
	${CC} -c ${TEST}dico_test.c ${FLAG} 

grille_test.o: ${TEST}grille_test.c
	${CC} -c ${TEST}grille_test.c ${FLAG} 

main_test.o: ${TEST}main_test.c ${JOB}
	${CC} -c ${TEST}main_test.c ${JOB} ${FLAG}
clean:
	rm -rf *.o
	rm -rf doc
doc:
	doxygen
