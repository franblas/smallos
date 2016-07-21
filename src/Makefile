OBJECTS = loader.o kmain.o io.o framebuffer.o gdt_asm.o gdt.o idt_asm.o idt.o isr_stub.o isr.o irq.o timer.o keyboard.o
CC = gcc
CFLAGS = -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector \
	-nostartfiles -nodefaultlibs -Wall -Wextra -Werror -c
LDFLAGS = -T link.ld -melf_i386
AS = nasm
ASFLAGS = -f elf

all: kernel.elf

kernel.elf: $(OBJECTS)
	ld $(LDFLAGS) $(OBJECTS) -o kernel.elf

smallos.iso: kernel.elf
	cp kernel.elf iso/boot/kernel.elf
	genisoimage -R                        \
				-b boot/grub/stage2             \
				-no-emul-boot                   \
				-boot-load-size 4               \
				-A os                           \
				-input-charset utf8             \
				-quiet                          \
				-boot-info-table                \
				-o smallos.iso                  \
				iso

run: smallos.iso

%.o: %.c
	$(CC) $(CFLAGS)  $< -o $@

%.o: %.s
	$(AS) $(ASFLAGS) $< -o $@

clean:
	rm -rf *.o kernel.elf smallos.iso iso/boot/kernel.elf

docker-run:
	docker run -v=$$(pwd):/code smallos:0.1 make clean run
