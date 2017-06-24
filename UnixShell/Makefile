CC=gcc

mysh:	cscd340Lab8.c ./tokenize/makeArgs.o ./utils/myUtils.o ./process/process.o ./pipes/pipes.o ./helper/Lab8Helper.o ./linkedlist/linkedList.o
	gcc -g cscd340Lab8.c ./tokenize/makeArgs.o ./utils/myUtils.o ./process/process.o ./pipes/pipes.o ./helper/Lab8Helper.o ./linkedlist/linkedList.o -o mysh

makeArgs.o:	./tokenize/makeArgs.c ./tokenize/makeArgs.h
	gcc -g -c ./tokenize/makeArgs.c

myUtils.o:	./utils/myUtils.o ./utils/myUtils.h
	gcc -g -c ./utils/myUtils.c

process.o:	./process/process.c ./process/process.h
	gcc -g -c ./process/process.c	

pipes.o:	./pipes/pipes.c ./pipes/pipes.h
	gcc -g -c ./pipes/pipes.c

Lab8Helper.o:    ./helper/Lab8Helper.c ./helper/Lab8Helper.h
	gcc -g -c ./helper/Lab8Helper.c
linkedList.o:	./linkedlist/linkedList.c ./linkedlist/linkedList.h
	gcc -g -c ./linkedlist/linkedList.c

clean:
	rm ./pipes/pipes.o	
	rm ./utils/myUtils.o
	rm ./process/process.o
	rm ./tokenize/makeArgs.o
	rm ./helper/Lab8Helper.o
	rm ./linkedlist/linkedList.o
	rm mysh

