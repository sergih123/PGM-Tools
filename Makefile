BIN=bin
INC=include
OBJ=obj
LIB=lib
SRC=src

all : bin/main

$(OBJ)/imagenES.o: $(SRC)/imagenES.cpp $(INC)/imagenES.h
	g++ -c -o $(OBJ)/imagenES.o -I$(INC) $(SRC)/imagenES.cpp

$(OBJ)/imagen.o: $(SRC)/imagen.cpp $(INC)/imagen.h
	g++ -c -o $(OBJ)/imagen.o -I$(INC) $(SRC)/imagen.cpp

$(OBJ)/main.o: $(SRC)/main.cpp $(INC)/imagenES.h $(INC)/imagen.h 
	g++ -c -o $(OBJ)/main.o -I$(INC) $(SRC)/main.cpp

$(BIN)/main: $(OBJ)/main.o $(OBJ)/imagenES.o $(OBJ)/imagen.o
	g++ -o $(BIN)/main $(OBJ)/main.o $(OBJ)/imagenES.o $(OBJ)/imagen.o

clean:
	echo "Limpieza de objetos..."
	rm $(OBJ)/*.o

mrproper: clean
	rm $(BIN)/main