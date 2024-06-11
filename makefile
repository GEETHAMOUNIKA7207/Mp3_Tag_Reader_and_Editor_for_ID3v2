OBJ=$(patsubst %.c, %.o, $(wildcard *.c))
res.out : $(OBJ)
	gcc -o $@ $^
clear :
	rm *.c *.out

