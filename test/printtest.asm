mov ah, 0eh
mov al, '$'
int 10h
inc al
int 10h
jmp $