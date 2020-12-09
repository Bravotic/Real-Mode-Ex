mov dh, 0
mov dl, 0
mov al, '='
loop:
    cmp dl, 80
    je .done
    mov ah, 0eh
    int 10h
    inc dl
    mov ah, 2
    int 10h
    jmp loop
    .done:
        cmp dh, 25
        je .donedone
        mov dh, 25
        mov dl, 0
        mov ah, 2
        int 10h
 
        jmp loop
    .donedone:
        jmp $