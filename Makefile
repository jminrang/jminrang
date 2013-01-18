SRCS	= $(shell find -name '*.[cS]')
OBJS	= $(addsuffix .o,$(basename $(SRCS)))

CC		= gcc
LD		= ld
ASM		= nasm
OBJDUMP	= objdump -d

ASFLAGS	= -m32
CFLAGS	= -m32 -Wall -g -I./include/ -fno-stack-protector -fno-builtin -pipe 
LDFLAGS = -melf_i386 -Tkernel.ld

TARGET	= kernel
SYM		= kernel.sym

all: check_machine $(TARGET) t

$(TARGET):	$(OBJS)
	@$(LD) $(LDFLAGS) -o $@ $^ -Map ./debug/System.map
	@objcopy --only-keep-debug $(TARGET) $(SYM)

%.o:	%.c
	@echo "CC  "$<
	@$(CC) $(CFLAGS) -c -o $@ $^
	@$(OBJDUMP) $@ > $(patsubst %.o,%.txt,$@)
	@mv ./src/*.txt ./debug/

%.o:	%.S
	@echo "ASM "$<
	@$(CC) $(ASFLAGS) -c -o $@ $^

check_machine:
	@clear
	@./sh_version_check.sh
	@echo""
	@echo""
c:		clean
clean:
	@clear
	@rm $(OBJS) $(TARGET) Env.txt ./debug/* $(SYM)

t:		test
test:
	@qemu-system-x86_64 -kernel kernel -M pc -m 1024 -s -monitor stdio -no-reboot -no-shutdown

g:		gdb
gdb:	$(TARGET)	.gdbinit
	@qemu-system-x86_64 -kernel kernel -M pc -m 1024 -s -S -no-reboot -no-shutdown &
	@gdb -q -iex "set auto-load safe-path ./"

line:
	@find ./ -name *.[chs] -or -name *.asm -or -name *.ld -or -name *.sh | xargs cat | wc -l

.PHONY: clean
