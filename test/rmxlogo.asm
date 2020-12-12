mov si, rmxlogo1
mov ah, 0eh

loop1:
    mov al, [si]
    cmp al, 0
    je .done1
    int 10h
    inc si
    jmp loop1
.done1:
    jmp $

rmxlogo1: db "8888888b. 888b     d888         ",10
rmxlogo2: db "888   Y88b8888b   d8888         ",10
rmxlogo3: db "888    88888888b.d88888         ",10
rmxlogo4: db "888   d88P888Y88888P888888  888 ",10
rmxlogo5: db "8888888P' 888 Y888P 888`Y8bd8P' ",10
rmxlogo6: db "888 T88b  888  Y8P  888  X88K   ",10
rmxlogo7: db "888  T88b 888   '   888.d8''8b. ",10
rmxlogo8: db "888   T88b888       888888  888 ",10,10
rmxlogo9: db "          Real Mode Ex          ", 10
rmxlogoa: db "The x86 Real Mode Virtual Machine",10,10
rmxlogob: db "https://github.com/Bravotc/Real-Mode-Ex",10
rmxlogoc: db "https://bravotic.com/real-mode-ex",10,0
