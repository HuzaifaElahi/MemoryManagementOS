  
myKernel 	: shell.o kernel.o interpreter.o cpu.o ram.o pcb.o shellmemory.o
		gcc -o myKernel shell.o kernel.o interpreter.o cpu.o ram.o pcb.o shellmemory.o

shell.o	 	: shell.c shell.h
		gcc -c shell.c 
kernel.o 	: kernel.c kernel.h
		gcc -c kernel.c
interpreter.o 	: interpreter.c interpreter.h
		gcc -c interpreter.c
cpu.o		: cpu.c cpu.h
		gcc -c cpu.c
ram.o		: ram.c ram.h
		gcc -c ram.c
pcb.o		: pcb.c pcb.h
		gcc -c pcb.c
shellmemory.o	: shellmemory.c shellmemory.h
		gcc -c shellmemory.c
clean		: 
		rm myKernel shell.o kernel.o interpreter.o cpu.o ram.o pcb.o shellmemory.o