shopt -s nullglob
shopt -s globstar

echo -e "\n#### Compiling ####\n"

find code -name '*' -type d -print0 | xargs -0 -I file mkdir workdir/file
find code -name '*.asm' -print0 | xargs -0 -I file bash -c 'echo "A: file"; nasm -f elf32 file -o workdir/file.o;'
find code -name '*.c' -print0 | xargs -0 -I filez bash -c 'echo "C: filez"; gcc -m32 -std=c99 -ffreestanding -O2 -Wall -Wno-unused-parameter -Wno-unused-variable -Wextra -nostdlib -nostartfiles -nodefaultlibs -c filez -o workdir/filez.o;'
echo -e "\n#### Linking ####\n"
ld -m elf_i386 -O2 -T link.ld -o workdir/kernel.bin workdir/code/**/*.o

echo -e "\n#### Creating ISO ####\n"
mkdir -p workdir/iso/boot/grub
touch workdir/iso/boot/grub/grub.cfg
echo -e "menuentry \"NemeDerpOS 420\" {\n" >> workdir/iso/boot/grub/grub.cfg
echo -e "\tmultiboot /boot/kernel.bin\n" >> workdir/iso/boot/grub/grub.cfg
echo -e "}" >> workdir/iso/boot/grub/grub.cfg
mv workdir/kernel.bin workdir/iso/boot/
grub-mkrescue -o boot.iso workdir/iso
echo -e "\n#### Cleaning up ####\n"
find workdir -name '*.asm.o' -print0 | xargs -0 -I file bash -c 'echo "A: file"; rm file;'
find workdir -name '*.c.o' -print0 | xargs -0 -I file bash -c 'echo "C: file"; rm file;'
rm -r workdir/*
echo -e "\n#### Running ####\n"
#qemu-system-x86_64 -monitor stdio -m 8192M -smp sockets=1,cores=4,threads=1 -cdrom boot.iso -boot d
