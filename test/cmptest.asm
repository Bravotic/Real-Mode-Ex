mov al, 5

cmp al, 5
je equal
jne nequal

mov ah, 0x55
jmp $

equal:
mov ah, 0x50
jmp $

nequal:
mov ah, 0x25
jmp $
