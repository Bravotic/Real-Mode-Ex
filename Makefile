CFLAGS ?= -std=c99 -I ./include -O2 -Wall -Wextra -Wpedantic -Wconversion -Wcast-align -Wunused -Wshadow -Wpointer-arith -Wcast-qual -Wno-missing-braces

CFLAGS += -D_RMX_PARSER_NO_STOP
CFLAGS += -D_RMX_NO_ERROR

CFLAGS += -I ./runtime/libc/include
CFLAGS += -I ./runtime/cross/include/

#CFLAGS += -lncurses

vm: error.o ivt.o loader.o mem.o parser.o registers.o vm.o handler.o 10h.o textmode.o
	$(CC) $(CFLAGS) -c runtime/libc/re/re.c
	$(CC) $(CFLAGS) -c runtime/libc/re/int_hle.c
	$(CC) -lncurses *.o -o rmx-vm

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
textmode.o: runtime/cross/lib/curses/textmode.c
	$(CC) $(CFLAGS) -c runtime/cross/lib/curses/textmode.c

.PHONY: clean
clean:
	rm *.o rmx-vm*
