bcc -ansi -c -o kernel.o kernel.c 
bcc -ansi -c -o shell.o shell.c
as86 lib.asm -o lib.o
as86 kernel.asm -o kernel_asm.o
ld86 -o kernel -d kernel.o kernel_asm.o
ld86 -o shell -d shell.o lib.o
dd if=kernel of=floppya.img bs=512 conv=notrunc seek=3
dd if=map.img of=floppya.img bs=512 count=1 seek=1 conv=notrunc
dd if=dir.img of=floppya.img bs=512 count=1 seek=2 conv=notrunc
#gcc -o loadFile loadFile.c
./loadFile shell
./loadFile message.txt
./loadFile tstprg
./loadFile tstpr2
bochs -f config.bxrc
