mov ah, 0eh

mov si, hello_world

loop:

    mov al, [si]
    cmp al, 0
    je .done

    int 10h
    inc si
    jmp loop
.done:

    
mov si, test

oloop:

    mov al, [si]
    cmp al, 0
    je .odone

    int 10h
    inc si
    jmp oloop
.odone:
    
    jmp $

hello_world: db "Hello, world!", 0
test: db "  This is a demonstration of the new RMX parser", 10, 0
