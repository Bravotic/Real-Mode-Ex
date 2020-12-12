CFLAGS ?= -std=c99 -O2 -I ./include -Wall -Wextra -Wpedantic -Wconversion -Wcast-align -Wunused -Wshadow -Wpointer-arith -Wcast-qual -Wno-missing-braces

CFLAGS += -D_RMX_PARSER_NO_STOP
CFLAGS += -D_RMX_NO_ERROR
CFLAGS += -D_RMX_BAREMETAL


CFLAGS += -nostdinc -nostartfiles -nodefaultlibs 

vm: error.o ivt.o loader.o mem.o misc.o parser.o registers.o vm.o handler.o
	$(CC) $(CFLAGS) -c runtime/bare/x86_64-linux/re/re.c
	$(CC) $(CFLAGS) *.o -o rmx-vm

error.o: lib/rmx/error.c
	$(CC) $(CFLAGS) -c lib/rmx/error.c
ivt.o: lib/rmx/ivt.c
	$(CC) $(CFLAGS) -c lib/rmx/ivt.c
loader.o: lib/rmx/loader.c
	$(CC) $(CFLAGS) -c lib/rmx/loader.c
mem.o: lib/rmx/mem.c
	$(CC) $(CFLAGS) -c lib/rmx/mem.c
misc.o: lib/rmx/misc.c
	$(CC) $(CFLAGS) -c lib/rmx/misc.c
parser.o: lib/rmx/parser.c
	$(CC) $(CFLAGS) -c lib/rmx/parser.c
registers.o: lib/rmx/registers.c
	$(CC) $(CFLAGS) -c lib/rmx/registers.c
vm.o: lib/rmx/vm.c
	$(CC) $(CFLAGS) -c lib/rmx/vm.c
handler.o: lib/hle/handler.c
	$(CC) $(CFLAGS) -c lib/hle/handler.c

.PHONY: clean
clean:
	rm *.o rmx-vm*
