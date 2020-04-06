title Something (matrix.asm)

.model small
.486
.stack 100h

.data
Xc dw 0
Yc dw 0
saveInt label word
dword ?

.code

myInt proc
	cli
		mov ax,4c00h
		int 21h
		push ds
		mov ax, offset saveInt+2
		mov ds, ax
		mov dx, offset saveInt
		mov ah,25h
		mov al,9h
		int 21h
		pop ds
	sti	
	iret
myInt endp

printLine proc
	push cx
	mov cx, 79
	
	L1:
		call printEvery
		loop L1
	pop cx
	ret
printLine endp

moveDown proc
	push cx
	push si
	
	call lastPos
	mov cx, 25
	L2:
		call moveLine
		sub si, 160
		loop l2
	pop si
	pop cx
	ret
moveDown endp

lastPos proc
	push ax
	push bx
	
	mov ax, 160
	mov bx, 24
	mul bx
	mov si, ax
	
	pop bx
	pop ax
	ret
lastPos endp

moveLine proc
	push cx
	push si
	mov cx, 79
	L3:
		call moveChar
		add si, 2
		loop L3
	pop si
	pop cx
	ret
moveLine endp

moveChar proc
	push ax
	push cx

	mov al, es:[si]
	mov es:[si+160], al
	mov es:[si+161], 00000010b

	pop cx
	pop ax
	ret
moveChar endp
	
printEvery proc
	call longRandom
	mov eax, edx
	call longRandom
	cmp edx, eax
	jg Spacemaker
	jmp noSpace
	Spacemaker:
			mov ax, " "
	Nospace:
			mov es:[si], al
			mov es:[si+1], 00000010b
			add si, 2
	ret
printEvery endp
	
busyWait proc		
	push ecx	
	mov ecx, 01FFFFFFFh
	LA:
		cmp ecx, 0
		je LB
		dec ecx
		jmp LA
	LB:
		pop ecx
		ret
busyWait endp

longRandom proc
	.data
	seed DWORD 12345678h
	.code
	mov eax, 343FDH
	mul seed
	xor edx, edx
	add eax, 269EC3h
	mov seed, eax
	ror eax, 8
	shld edx, eax, 16
	ret
longRandom endp

main proc
	mov ah, 35
	mov al, 9
	int 21h
	mov saveInt, bx
	mov saveInt+2, es
		
	call busyWait

	push ds
	mov ax, @code
	mov ds, ax
	mov ah, 25h
	mov al, 9
	mov dx, offset myInt
	pop ds

	mov ax, @data
	mov ds, ax

	mov ax, 0b800h
	mov es, ax

	mov ah, 0
	mov al, 3
	int 10h
	
	mov ax, 3
	int 33h
	mov Xc, cx
	mov Yc, dx
	Begin:
		cmp Xc, cx
		jne exit
		cmp Yc, dx
		jne exit
		cmp Bx, 0
		jne exit
		
		mov si, 0
		call printLine
		call busyWait
		call moveDown

		mov ax, 3
		int 33h
		jmp Begin
	Exit:
		mov ax, 4c00h
		int 21h
main endp
	
end main
