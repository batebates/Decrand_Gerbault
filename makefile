CC=gcc
FLAG=-Wall -W -g
OBJ= dico.o main.o grille.o
JOB= ./include/*.h
SRC=./src/
TEST=./src/tests/
all:ruzzle.exe test_1.exe test_2.exe clean doc

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

test_1.exe: main_test1.o
	${CC} -o ./tests/test_1.exe  main_test1.o ${FLAG} -lcunit
 
main_test1.o: ${TEST}main_test1.c
	${CC} -c ${TEST}main_test1.c  -lcunit ${FLAG}
test_2.exe: main_test2.o
	${CC} -o ./tests/test_2.exe  main_test2.o ${FLAG} -lcunit
 
main_test2.o: ${TEST}main_test2.c
	${CC} -c ${TEST}main_test2.c -lcunit ${FLAG}
clean:
	rm -rf *.o
	rm -rf doc
doc:
	doxygen
