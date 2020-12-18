loop:
mov ah, 0
int 16h
mov ah, 0eh
int 10h
jmp loop
