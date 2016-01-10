nasm -f elf32 entry.asm -o entry.o
gcc -m32 -c kernel.c -o kernel.o
gcc -m32 -c idt.c -o idt.o
gcc -m32 -c keyboard.c -o keyboard.o
gcc -m32 -c screen.c -o screen.o
gcc -m32 -c command.c -o command.o
ld -m elf_i386 -T link.ld -o kernel entry.o kernel.o idt.o keyboard.o screen.o command.o
rm kernel.o
rm entry.o
rm keyboard.o
rm idt.o
rm screen.o
rm command.o
qemu-system-i386 -kernel kernel
