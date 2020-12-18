CFLAGS ?= -std=c99 -I ./include -O0 -Wall -Wextra -Wpedantic -Wconversion -Wcast-align -Wunused -Wshadow -Wpointer-arith -Wcast-qual -Wno-missing-braces

CFLAGS += -D_RMX_PARSER_NO_STOP

CFLAGS += -I ./runtime/libc/include
CFLAGS += -I ./runtime/cross/include/

CFLAGS += $(shell sdl2-config --cflags) -DSDL2

LDFLAGS += $(shell sdl2-config --libs)

CFLAGS += -D_RMX_TEXTMODE_DEF

vm: error.o ivt.o loader.o mem.o parser.o registers.o vm.o handler.o 10h.o 16h.o textmode.o font.o psf.o
	$(CC) $(CFLAGS) -c runtime/libc/re/re.c
	$(CC) $(CFLAGS) -c runtime/libc/re/int_hle.c
	$(CC) *.o $(LDFLAGS) -o rmx-vm

error.o: lib/rmx/error.c
	$(CC) $(CFLAGS) -c lib/rmx/error.c
ivt.o: lib/rmx/ivt.c
	$(CC) $(CFLAGS) -c lib/rmx/ivt.c
loader.o: lib/rmx/loader.c
	$(CC) $(CFLAGS) -c lib/rmx/loader.c
mem.o: lib/rmx/mem.c
	$(CC) $(CFLAGS) -c lib/rmx/mem.c
parser.o: lib/rmx/parser.c
	$(CC) $(CFLAGS) -c lib/rmx/parser.c
registers.o: lib/rmx/registers.c
	$(CC) $(CFLAGS) -c lib/rmx/registers.c
vm.o: lib/rmx/vm.c
	$(CC) $(CFLAGS) -c lib/rmx/vm.c
handler.o: lib/hle/handler.c
	$(CC) $(CFLAGS) -c lib/hle/handler.c
10h.o: runtime/libc/hle/int/10h.c
	$(CC) $(CFLAGS) -c runtime/libc/hle/int/10h.c
16h.o: runtime/libc/hle/int/16h.c
	$(CC) $(CFLAGS) -c runtime/libc/hle/int/16h.c
textmode.o: runtime/cross/lib/sdl2/textmode.c
	$(CC) $(CFLAGS) -c runtime/cross/lib/sdl2/textmode.c
font.o: adjunct/font.psf
	objcopy -O elf64-x86-64 -B i386 -I binary adjunct/font.psf font.o
psf.o: runtime/cross/lib/psf/psf.c
	$(CC) $(CFLAGS) -c runtime/cross/lib/psf/psf.c

.PHONY: clean
clean:
	rm *.o rmx-vm*
