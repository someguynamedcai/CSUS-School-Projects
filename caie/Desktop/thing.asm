title MatrixThing
.model large
.486
.stack 100h
Public _LongRandom
.data
row dw 0;
column dw 1;
seed DWORD 12345678h;
saveInt label word
Xc dw 0
Yc dw 0
.code

myInt proc
	cli
		mov ax,4c00h
		int 21h
		push ds
		mov ax, offset saveInt+2
		mov ds, ax
		mov dx, offset saveInt
		mov ah, 25h
		mov al, 9h
		int 21h
		pop ds
	sti	
	iret
myInt endp


Display proc
	mov bx, row
	mov cx, column
	mov dx, 10

	mov ax,160
	mul cx
	shl bx,1
	add bx,ax
	call _LongRandom
	mov eax,edx
	call _LongRandom
	cmp edx, eax
	jg Spacemaker
	jmp Nospace
	Spacemaker:
			mov ax, " "

	Nospace:
			mov ah, 0ah
			mov es:[bx],ax
	ret
Display endp


Clear proc
	push bx
	mov bx, 0
	mov al," "
	mov ah,07h
	
	Clearscreen:
		mov es:[bx],ax
		inc bx
		inc bx
		cmp bx, 7000
		jle Clearscreen
		pop bx
		ret
Clear endp

_LongRandom proc
	mov eax, 343FDh
	mul seed
	xor edx,edx
	add eax, 26933h
	mov seed, eax
	ror eax, 8
	shld edx,eax,16
	ret
_LongRandom endp

busyWait proc
	push ecx
	mov ecx, 01FFFFFFh
	L1:
		cmp ecx, 0
		je L2
		dec ecx
		jmp L1
	L2:
		pop ecx
		ret
busyWait endp

fillLine proc
	Loop1:
		call Display
		inc row
		cmp row, 79
		jle Loop1
	ret
fillLine endp

movLine proc
	push cx
	push si
	mov cx, 79
	
	L12:
		call movChar
		add si, 2
		loop L12
	pop si
	pop cx
	ret	
movLine endp

movChar proc
	push ax
	push cx
	
	mov al, es:[si]
	mov es:[si+160],al
	mov es:[si+161],00000010b
	
	pop cx
	pop ax
	ret
movChar endp

movDown proc
	push cx
	push si
	
	call lastPos
	mov cx,25
	L13:
		call movLine
		sub si, 160
		loop L13
	pop si
	pop cx
	ret
movDown endp

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

main proc
	mov ah,35
	mov al,9
	int 21h
	mov saveInt, bx
	mov saveInt+2,es

	call busywait
	push ds	

	mov ax,@data
	mov ds,ax
	mov ah,25h
	mov al,9
	mov dx,offset myInt
	int 21h
	pop ds
	
	mov ax, @data
	mov ds, ax
	
	mov ax,0b800H
	mov es,ax

	mov ax, 3
	int 33h
	mov Xc, cx
	mov Yc, dx
	
	call Clear
	mov bx, 0
	mov cx, 0
	mov al, 0

LoopDis:
	cmp Xc, cx
	jne Stop
	cmp Yc,dx
	jne Stop
	cmp bx, 0
	jne Stop
	
	mov si, 0
	call fillLine
	call busyWait
	call movDown
	
	mov ax,3
	int 33h
	jmp LoopDis

Stop:
	mov ax, 4c00h
	int 21h
	
main endp

end main
