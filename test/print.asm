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
    
    jmp $

hello_world: db "Hello, world!", 0
