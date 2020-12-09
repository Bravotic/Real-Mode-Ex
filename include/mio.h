
#define SYSCALL_READ    0
#define SYSCALL_WRITE   1
#define SYSCALL_OPEN    2

#define BUFFER_SIZE     1024

#ifndef __GNUC__
    #define __asm__ asm
#endif

// Print macro
// @param msg   - message to print
// Basically just make everything easier
#define size_of(buf)    find(buf, (char)0x0)
#define print(msg)      put(1, msg, size_of(msg))
#define buffer()        char buf[BUFFER_SIZE] = {(char) 0x0};
#define read()          get(0, buf, BUFFER_SIZE)
#define clear_buf()     for(int i = 0; buf[i] != (char)0x0; i++){ buf[i] = 0x0; }

#define isnum(chnum)    ((int)chnum >= 48 && (int)chnum <= 57) 

//int size_of(char *buf){
//    int i;
//    for(i = 0; buf[i] != (char)0x0; i++);
//    return i;
//}

int find(char* buf, char fn){
    int i = 0;
    for (i = 0; buf[i] != fn && buf[i] != (char)0x0; i++);
    return i;
}

int nthdigit(int x, int n)
{
    while (n--) {
        x /= 10;
    }
    return (x % 10);
}

int lenint(int i){
    int pow = 1;
    while(1){
        if( i < 10)
        {
            return 1;
        }
        else if( i >= pow * 10 && i < (pow * 10) * 10){
            return pow;
        }
        else{
            pow++;
        }
    }

}

char* itoc( int i, char* rn){
    int lel = lenint(i);
    for ( int x = 0; x < lel; x++){
        rn[lel - x] = nthdigit(i, x) + 48;    
    }
    return rn;
}

// x86_64 put function
// @param fd    - file descriptor - same as the syscalls (literally directly passed to it)
// @param buf   - text buffer - what will be displayed
// @param size  - size of text buffer - needed for asm (if it was up to me i'd terminate at null)
int put(int fd, char *buf, int size){
    // This was made while listening to the sweet sounds of Homecoming by Greenday
    int ret;
    asm volatile(
        "syscall"
        : "=a" (ret)
        : "a"(SYSCALL_WRITE), "D"(fd), "S"(buf), "d"(size)
        : "cc", "rcx", "r11", "memory");
    return ret;
}

char* get(int fd, char* ret, int size){
    int reti;
    asm volatile(
        "syscall"
        : "=r" (reti)
        : "a"(SYSCALL_READ), "S"(ret), "D"(fd), "d"(size)
        : "cc", "rcx", "r11", "memory");
    return ret;
    
}

int open(char* name, int flags, int mode){
    int ret = 2;
    asm volatile(
        "syscall"
        : "=r" (ret)
        : "a"(2), "S"(flags), "D"(name), "d"(mode)
        : "cc", "rcx", "r11", "memory");
    return ret;
}
int close(int fd){
    int ret = 2;
    asm volatile(
        "syscall"
        : "=r" (ret)
        : "a"(3), "D"(fd)
        : "cc", "rcx", "r11", "memory");
    return ret;
}

void handle_error(int errno){
#ifdef EXTRA_ERRORS
    switch(errno){
        case 1:
            print("ERR: Operation not permitted\n");
        break;
        case 2:
            print("ERR: No such file or directory\n");

    }
#else
    print("An error occured, enable EXTRA_ERRORS at compilation for more info\n");
#endif
}


