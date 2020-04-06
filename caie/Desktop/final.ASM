title screen	(screens.asm)

.model small
.486
.stack 100h

.data
Xc DW 0
Yc DW 0
int9save label word
dword ?

.code

myInt proc
	cli
		mov ax,4c00h
		int 21h
		push ds
		mov ax,offset int9save+2
		mov ds, ax
		mov dx,offset int9Save
		mov ah,25h
		mov al,9h
		int 21h
		pop ds
	sti
	iret
myInt endp

main PROC
	mov ah,35
	mov al,9
	int 21h
	mov int9Save, BX
	mov int9Save+2,ES

	call busywait

	push ds
	mov ax,@code
	mov ds,ax
	mov ah,25h
	mov al,9
	mov dx,offset myInt
	int 21h
	pop ds
	

	mov ax, @data
	mov ds, ax

	mov ax, 0b800h
	mov es, ax

	mov ah,0
	mov al,3 ; video mode 3 (color text)
	int 10h
	
	mov ax,3
	int 33h
	mov Xc, CX
	mov Yc, DX
	Start:
		cmp Xc,CX
		jne exit
		cmp Yc,DX
		jne exit
		cmp Bx,0
		jne exit

		mov si, 0
		call printLine
		call busyWait
		call moveDown
		
		mov Ax, 3
		int 33h
		jmp Start
	
	Exit:
		mov ax, 4c00h
		int 21h
main ENDP

printLine proc

	push cx

	mov cx, 79
	
	L1: 
		call printMsg	
		loop L1

	pop cx
	ret
printLine endp

moveDown PROC

	push cx
	push si

	call lastPos
	mov cx, 25		
	L100:
		call moveLine
		sub si, 160
		loop L100
		
	pop si
	pop cx
	ret	
moveDown ENDP

lastPos PROC

	push ax
	push bx

	mov ax, 160
	mov bx, 24
	mul bx
	mov si, ax

	pop bx
	pop ax
	ret
lastPos ENDP

moveLine PROC

	push cx
	push si
	mov cx, 79

	L1000:
		call moveChar
		add si, 2
		loop L1000

	pop si
	pop cx
	ret
moveLine ENDP

moveChar PROC

	push ax
	push cx

	mov al, es:[si]
	mov es:[si+160], al
	mov es:[si+161], 00000010b

	pop cx
	pop ax
	ret
moveChar ENDP

printMsg proc

	call longRandom
	cmp ax, 4FFFh
	JB noSpace
	mov al, 20h
	
	noSpace:
		mov es:[si], al
		mov es:[si+1], 00000010b
		add si,2

	ret
printMsg endp

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
END main
