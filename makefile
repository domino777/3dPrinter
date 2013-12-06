main.hex: main.elf
	avr-objcopy -j .text -j .data -O ihex main.elf main.hex
	
main.elf: main.o
	avr-gcc -w -mmcu=atxmega256a3b *.o -o main.elf

main.o: main.c
	find ./ -type f -name "*.c" -exec avr-gcc -I/home/domy/project/3dPrinter -w -mmcu=atxmega256a3b -O3 -std=c99 -c {} +

clean:
	rm *.o *.elf *.hex
