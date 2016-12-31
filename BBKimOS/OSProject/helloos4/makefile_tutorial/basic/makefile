excuteMe.exe : reply.o calc.o main.o
	gcc -o executeMe.exe reply.o calc.o main.o

reply.o : reply.c
	gcc -c -o reply.o reply.c

calc.o : calc.c
	gcc -c -o calc.o calc.c

main.o : main.c
	gcc -c -o main.o main.c

clean :
	rm *.o
