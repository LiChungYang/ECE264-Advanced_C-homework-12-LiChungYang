CFLAGS = -std=c99 -g -Wall -Wshadow --pedantic -Wvla -Werror
GCC = gcc $(CFLAGS) 
EXEC = hw12
OBJS =  hw12.o 
VALGRIND = valgrind --tool=memcheck --leak-check=yes --verbose --leak-check=full

$(EXEC): $(OBJS) calc.h
	$(GCC) $(OBJS) -o $(EXEC) 

all: $(EXEC)

test: $(EXEC)
	-./$(EXEC) inputs/test1 
	-./$(EXEC) inputs/test2 
	-./$(EXEC) inputs/test3 
	-./$(EXEC) inputs/test4 
	-./$(EXEC) inputs/test5 

memory: $(EXEC)
	$(VALGRIND) --log-file=log1 ./$(EXEC) inputs/test1
	$(VALGRIND) --log-file=log2 ./$(EXEC) inputs/test2
	$(VALGRIND) --log-file=log3 ./$(EXEC) inputs/test3
	$(VALGRIND) --log-file=log3 ./$(EXEC) inputs/test4
	$(VALGRIND) --log-file=log3 ./$(EXEC) inputs/test5

%.o : %.c
	$(GCC) -c $< 

clean:
	/bin/rm -f *.o
	/bin/rm -f $(EXEC)
	/bin/rm -f id? first? last? log?

