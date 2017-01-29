FLAGS = -ansi -Wall -pedantic -std=c99 -lm -lglut -lGLU -lGL -lXext
GCC=gcc
SRC=src

all:
			$(GCC) -o openGL $(FLAGS) $(SRC)/main.c $(SRC)/frame.c $(SRC)/arm.c $(SRC)/chest.c $(SRC)/foot.c $(SRC)/hand.c $(SRC)/head.c $(SRC)/leg.c $(SRC)/neck.c $(SRC)/hat.c $(SRC)/shoulder.c $(SRC)/chair.c $(SRC)/buttocks.c

clean:
			rm openGL
